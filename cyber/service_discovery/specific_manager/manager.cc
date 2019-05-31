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

#include "cyber/service_discovery/specific_manager/manager.h"

#include "cyber/common/global_data.h"
#include "cyber/common/log.h"
#include "cyber/message/message_traits.h"
#include "cyber/time/time.h"
#include "cyber/transport/qos/qos_profile_conf.h"
#include "cyber/transport/rtps/attributes_filler.h"
#include "cyber/transport/rtps/underlay_message.h"
#include "cyber/transport/rtps/underlay_message_type.h"

namespace apollo {
namespace cyber {
namespace service_discovery {

using transport::AttributesFiller;
using transport::QosProfileConf;

Manager::Manager()
    : is_shutdown_(false),
      is_discovery_started_(false),
      allowed_role_(0),
      change_type_(proto::ChangeType::CHANGE_PARTICIPANT),
      channel_name_(""),
      publisher_(nullptr),
      subscriber_(nullptr),
      listener_(nullptr) {
  host_name_ = common::GlobalData::Instance()->HostName();
  process_id_ = common::GlobalData::Instance()->ProcessId();
}

Manager::~Manager() { Shutdown(); }

bool Manager::StartDiscovery(RtpsParticipant* participant) {
  if (participant == nullptr) {
    return false;
  }
  if (is_discovery_started_.exchange(true)) {
    return true;
  }
  if (!CreatePublisher(participant) || !CreateSubscriber(participant)) {
    AERROR << "create publisher or subscriber failed.";
    StopDiscovery();
    return false;
  }
  return true;
}

void Manager::StopDiscovery() {
  if (!is_discovery_started_.exchange(false)) {
    return;
  }

  if (publisher_ != nullptr) {
    eprosima::fastrtps::Domain::removePublisher(publisher_);
    publisher_ = nullptr;
  }

  if (subscriber_ != nullptr) {
    eprosima::fastrtps::Domain::removeSubscriber(subscriber_);
    subscriber_ = nullptr;
  }

  if (listener_ != nullptr) {
    delete listener_;
    listener_ = nullptr;
  }
}

void Manager::Shutdown() {
  if (is_shutdown_.exchange(true)) {
    return;
  }

  StopDiscovery();
  signal_.DisconnectAllSlots();
}

bool Manager::Join(const RoleAttributes& attr, RoleType role,
                   bool need_publish) {
  if (is_shutdown_.load()) {
    ADEBUG << "the manager has been shut down.";
    return false;
  }
  RETURN_VAL_IF(!((1 << role) & allowed_role_), false);
  RETURN_VAL_IF(!Check(attr), false);
  ChangeMsg msg;
  Convert(attr, role, OperateType::OPT_JOIN, &msg);
  Dispose(msg);
  if (need_publish) {
    return Publish(msg);
  }
  return true;
}

bool Manager::Leave(const RoleAttributes& attr, RoleType role) {
  if (is_shutdown_.load()) {
    ADEBUG << "the manager has been shut down.";
    return false;
  }
  RETURN_VAL_IF(!((1 << role) & allowed_role_), false);
  RETURN_VAL_IF(!Check(attr), false);
  ChangeMsg msg;
  Convert(attr, role, OperateType::OPT_LEAVE, &msg);
  Dispose(msg);
  if (NeedPublish(msg)) {
    return Publish(msg);
  }
  return true;
}

Manager::ChangeConnection Manager::AddChangeListener(const ChangeFunc& func) {
  return signal_.Connect(func);
}

void Manager::RemoveChangeListener(const ChangeConnection& conn) {
  auto local_conn = conn;
  local_conn.Disconnect();
}

bool Manager::CreatePublisher(RtpsParticipant* participant) {
  RtpsPublisherAttr pub_attr;
  RETURN_VAL_IF(
      !AttributesFiller::FillInPubAttr(
          channel_name_, QosProfileConf::QOS_PROFILE_TOPO_CHANGE, &pub_attr),
      false);
  publisher_ =
      eprosima::fastrtps::Domain::createPublisher(participant, pub_attr);
  return publisher_ != nullptr;
}

bool Manager::CreateSubscriber(RtpsParticipant* participant) {
  RtpsSubscriberAttr sub_attr;
  RETURN_VAL_IF(
      !AttributesFiller::FillInSubAttr(
          channel_name_, QosProfileConf::QOS_PROFILE_TOPO_CHANGE, &sub_attr),
      false);
  listener_ = new SubscriberListener(
      std::bind(&Manager::OnRemoteChange, this, std::placeholders::_1));

  subscriber_ = eprosima::fastrtps::Domain::createSubscriber(
      participant, sub_attr, listener_);
  return subscriber_ != nullptr;
}

bool Manager::NeedPublish(const ChangeMsg& msg) const {
  (void)msg;
  return true;
}

void Manager::Convert(const RoleAttributes& attr, RoleType role,
                      OperateType opt, ChangeMsg* msg) {
  msg->set_timestamp(cyber::Time::Now().ToNanosecond());
  msg->set_change_type(change_type_);
  msg->set_operate_type(opt);
  msg->set_role_type(role);
  auto role_attr = msg->mutable_role_attr();
//  role_attr->CopyFrom(attr);
  role_attr->set_host_name(attr.host_name());
  role_attr->set_host_ip(attr.host_ip());
  role_attr->set_process_id(attr.process_id());
  role_attr->set_node_name(attr.node_name());
  role_attr->set_node_id(attr.node_id());
  role_attr->set_channel_name(attr.channel_name());
  role_attr->set_channel_id(attr.channel_id());
  role_attr->set_message_type(attr.message_type());
//  role_attr->set_proto_desc(attr.proto_desc());
  role_attr->set_id(attr.id());
//  role_attr->mutable_socket_addr()->CopyFrom(attr.socket_addr());
//  role_attr->mutable_qos_profile()->CopyFrom(attr.qos_profile());
//  role_attr->set_service_name(attr.service_name());
//  role_attr->set_service_id(attr.service_id());
  if (!role_attr->has_host_name()) {
    role_attr->set_host_name(host_name_);
  }
  if (!role_attr->has_process_id()) {
    role_attr->set_process_id(process_id_);
  }
}

void Manager::Notify(const ChangeMsg& msg) { signal_(msg); }

void Manager::OnRemoteChange(const std::string& msg_str) {
  if (is_shutdown_.load()) {
    ADEBUG << "the manager has been shut down.";
    return;
  }

  ChangeMsg msg;
  RETURN_IF(!message::ParseFromString(msg_str, &msg));
  if (IsFromSameProcess(msg)) {
    return;
  }
  RETURN_IF(!Check(msg.role_attr()));
  Dispose(msg);
}

bool Manager::Publish(const ChangeMsg& msg) {
  if (!is_discovery_started_.load()) {
    ADEBUG << "discovery is not started.";
    return true;
  }

  apollo::cyber::transport::UnderlayMessage m;
  RETURN_VAL_IF(!message::SerializeToString(msg, &m.data()), false);
  if (publisher_ != nullptr) {
    return publisher_->write(reinterpret_cast<void*>(&m));
  }
  return true;
}

bool Manager::IsFromSameProcess(const ChangeMsg& msg) {
  auto& host_name = msg.role_attr().host_name();
  int process_id = msg.role_attr().process_id();

  if (process_id != process_id_ || host_name != host_name_) {
    return false;
  }
  return true;
}

}  // namespace service_discovery
}  // namespace cyber
}  // namespace apollo
