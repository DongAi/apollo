/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "cyber/croutine/croutine.h"

#include <utility>

#include "cyber/base/concurrent_object_pool.h"
#include "cyber/common/global_data.h"
#include "cyber/common/log.h"
#include "cyber/croutine/detail/routine_context.h"
#include "cyber/event/perf_event_cache.h"

namespace apollo {
namespace cyber {
namespace croutine {

using apollo::cyber::event::PerfEventCache;
using apollo::cyber::event::SchedPerf;

thread_local volatile CRoutine *CRoutine::current_routine_ = nullptr;
thread_local volatile char *CRoutine::main_stack_ = nullptr;

namespace {
std::shared_ptr<base::CCObjectPool<RoutineContext>> context_pool = nullptr;
std::once_flag pool_init_flag;

void CRoutineEntry(void *arg) {
  CRoutine *r = static_cast<CRoutine *>(arg);
  r->Run();
  CRoutine::Yield(RoutineState::FINISHED);
}
}

CRoutine::CRoutine(const std::function<void()> &func) : func_(func) {
  std::call_once(pool_init_flag, [&]() {
    auto routine_num = 100;
    auto &global_conf = common::GlobalData::Instance()->Config();
    if (global_conf.has_scheduler_conf() &&
        global_conf.scheduler_conf().has_routine_num()) {
      routine_num = global_conf.scheduler_conf().routine_num();
    }
    context_pool.reset(new base::CCObjectPool<RoutineContext>(routine_num));
  });

  context_ = context_pool->GetObject();
  if (context_ == nullptr) {
    AWARN << "Maximum routine context number exceeded! Please check "
             "[routine_num] in config file.";
    context_.reset(new RoutineContext());
  }

  MakeContext(CRoutineEntry, this, context_.get());
  state_ = RoutineState::READY;
  updated_.test_and_set(std::memory_order_release);
}

CRoutine::~CRoutine() { context_ = nullptr; }

RoutineState CRoutine::Resume() {
  if (unlikely(force_stop_)) {
    state_ = RoutineState::FINISHED;
    return state_;
  }

  if (unlikely(state_ != RoutineState::READY)) {
    AERROR << "Invalid Routine State!";
    return state_;
  }

  current_routine_ = this;
  PerfEventCache::Instance()->AddSchedEvent(
      SchedPerf::SWAP_IN, id_, processor_id_, static_cast<int>(state_));
  SwapContext(GetMainStack(), GetStack());
  PerfEventCache::Instance()->AddSchedEvent(
      SchedPerf::SWAP_OUT, id_, processor_id_, static_cast<int>(state_));
  current_routine_ = nullptr;
  return state_;
}

void CRoutine::Stop() { force_stop_ = true; }

}  // namespace croutine
}  // namespace cyber
}  // namespace apollo
