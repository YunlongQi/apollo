/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

/**
 * @file
 **/
#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Eigen/Dense"
#include "cyber/common/log.h"
#include "modules/common/configs/proto/vehicle_config.pb.h"
#include "modules/common/configs/vehicle_config_helper.h"
#include "modules/common/math/vec2d.h"
#include "modules/common/vehicle_state/proto/vehicle_state.pb.h"
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/map/pnc_map/path.h"
#include "modules/map/pnc_map/pnc_map.h"
#include "modules/map/proto/map_id.pb.h"
#include "modules/planning/common/indexed_queue.h"
#include "modules/planning/common/obstacle.h"
#include "modules/planning/common/planning_gflags.h"
#include "modules/planning/common/trajectory/discretized_trajectory.h"

namespace apollo {
namespace planning {
class OpenSpaceInfo {
 public:
  OpenSpaceInfo();
  ~OpenSpaceInfo() = default;

  const size_t obstacles_num() const { return obstacles_num_; }
  size_t *mutable_obstacles_num() { return &obstacles_num_; }
  void set_obstacles_num(size_t obstacles_num) {
    obstacles_num_ = obstacles_num;
  }

  const Eigen::MatrixXi &obstacles_edges_num() const {
    return obstacles_edges_num_;
  }
  Eigen::MatrixXi *mutable_obstacles_edges_num() {
    return &obstacles_edges_num_;
  }

  const std::vector<std::vector<common::math::Vec2d>> &obstacles_vertices_vec()
      const {
    return obstacles_vertices_vec_;
  }
  std::vector<std::vector<common::math::Vec2d>>
      *mutable_obstacles_vertices_vec() {
    return &obstacles_vertices_vec_;
  }

  const Eigen::MatrixXd &obstacles_A() const { return obstacles_A_; }
  Eigen::MatrixXd *mutable_obstacles_A() { return &obstacles_A_; }

  const Eigen::MatrixXd &obstacles_b() const { return obstacles_b_; }
  Eigen::MatrixXd *mutable_obstacles_b() { return &obstacles_b_; }

  const double origin_heading() const { return origin_heading_; }
  double *mutable_origin_heading() { return &origin_heading_; }

  const common::math::Vec2d &origin_point() const { return origin_point_; }
  common::math::Vec2d *mutable_origin_point() { return &origin_point_; }

  const std::vector<double> &ROI_xy_boundary() const {
    return ROI_xy_boundary_;
  }
  std::vector<double> *mutable_ROI_xy_boundary() { return &ROI_xy_boundary_; }

  const std::vector<double> &open_space_end_pose() const {
    return open_space_end_pose_;
  }
  std::vector<double> *mutable_open_space_end_pose() {
    return &open_space_end_pose_;
  }

  const DiscretizedTrajectory &optimizer_trajectory_data() const {
    return optimizer_trajectory_data_;
  }

  DiscretizedTrajectory *mutable_optimizer_trajectory_data() {
    return &optimizer_trajectory_data_;
  }

  const std::vector<common::TrajectoryPoint> &stitching_trajectory_data()
      const {
    return stitching_trajectory_data_;
  }

  std::vector<common::TrajectoryPoint> *mutable_stitching_trajectory_data() {
    return &stitching_trajectory_data_;
  }

 private:
  // @brief obstacles total num including perception obstacles and parking space
  // boundary
  size_t obstacles_num_ = 0;

  // @brief the dimension needed for A and b matrix dimension in H
  // representation
  Eigen::MatrixXi obstacles_edges_num_;

  // @brief in the order of [x_min, x_max, y_min, y_max];
  std::vector<double> ROI_xy_boundary_;

  // @brief open_space end configuration in order of x, y, heading and speed.
  // Speed is set to be always zero now for parking
  std::vector<double> open_space_end_pose_;

  // @brief vector storing the vertices of obstacles in counter-clock-wise order
  std::vector<std::vector<common::math::Vec2d>> obstacles_vertices_vec_;

  // @brief Linear inequality representation of the obstacles Ax>b
  Eigen::MatrixXd obstacles_A_;
  Eigen::MatrixXd obstacles_b_;

  // @brief origin heading for planning space rotation
  double origin_heading_ = 0.0;

  // @brief origin point for scaling down the numeric value of the optimization
  // problem in order of x , y
  common::math::Vec2d origin_point_;

  DiscretizedTrajectory optimizer_trajectory_data_;

  std::vector<common::TrajectoryPoint> stitching_trajectory_data_;
};
}  // namespace planning
}  // namespace apollo
