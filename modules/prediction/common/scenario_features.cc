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
#include "modules/prediction/common/scenario_features.h"

#include "cybertron/common/log.h"

namespace apollo {
namespace prediction {

void ScenarioFeatures::set_ego_velocity(const double ego_velocity) {
  ego_velocity_ = ego_velocity;
}

double ScenarioFeatures::get_ego_velocity() const {
  return ego_velocity_;
}

void ScenarioFeatures::set_ego_acceleration(const double ego_acceleration) {
  ego_acceleration_ = ego_acceleration;
}

double ScenarioFeatures::get_ego_acceleration() const {
  return ego_acceleration_;
}

bool ScenarioFeatures::has_ego_lane() const {
  return has_ego_lane_;
}

void ScenarioFeatures::reset_ego_lane() {
  has_ego_lane_ = false;
}

void ScenarioFeatures::SetEgoLane(const std::string& lane_id,
    const double lane_s) {
  has_ego_lane_ = true;
  ego_lane_id_ = lane_id;
  ego_lane_s_ = lane_s;
}

std::pair<std::string, double> ScenarioFeatures::GetEgoLane() const {
  CHECK(has_ego_lane_);
  return {ego_lane_id_, ego_lane_s_};
}

bool ScenarioFeatures::has_left_neighbor_lane() const {
  return has_left_neighbor_lane_;
}

void ScenarioFeatures::reset_left_neighbor_lane() {
  has_left_neighbor_lane_ = false;
}

void ScenarioFeatures::SetLeftNeighborLane(const std::string& lane_id,
    const double lane_s) {
  has_left_neighbor_lane_ = true;
  left_neighbor_lane_id_ = lane_id;
  left_neighbor_lane_s_ = lane_s;
}

std::pair<std::string, double> ScenarioFeatures::GetLeftNeighborLane() const {
  CHECK(has_left_neighbor_lane_);
  return {left_neighbor_lane_id_, left_neighbor_lane_s_};
}

bool ScenarioFeatures::has_right_neighbor_lane() const {
  return has_right_neighbor_lane_;
}

void ScenarioFeatures::reset_right_neighbor_lane() {
  has_right_neighbor_lane_ = false;
}

void ScenarioFeatures::SetRightNeighborLane(const std::string& lane_id,
    const double lane_s) {
  has_right_neighbor_lane_ = true;
  right_neighbor_lane_id_ = lane_id;
  right_neighbor_lane_s_ = lane_s;
}

std::pair<std::string, double> ScenarioFeatures::GetRightNeighborLane() const {
  CHECK(has_right_neighbor_lane_);
  return {right_neighbor_lane_id_, right_neighbor_lane_s_};
}

bool ScenarioFeatures::has_front_junction() const {
  return has_front_junction_;
}

void ScenarioFeatures::reset_front_junction() {
  has_front_junction_ = false;
}

void ScenarioFeatures::SetFrontJunction(const std::string& junction_id,
    const double dist) {
  has_front_junction_ = true;
  front_junction_id_ = junction_id;
  dist_to_front_junction_ = dist;
}

std::pair<std::string, double> ScenarioFeatures::GetFrontJunction() const {
  CHECK(has_front_junction_);
  return {front_junction_id_, dist_to_front_junction_};
}

void ScenarioFeatures::AddObstacleId(const int obstacle_id) {
  obstacle_ids_.push_back(obstacle_id);
}

const std::vector<int>& ScenarioFeatures::get_obstacle_ids() const {
  return obstacle_ids_;
}

}  // namespace prediction
}  // namespace apollo
