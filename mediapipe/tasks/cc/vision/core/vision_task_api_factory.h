/* Copyright 2022 The MediaPipe Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef MEDIAPIPE_TASKS_CC_VISION_CORE_BASE_VISION_TASK_API_FACTORY_H_
#define MEDIAPIPE_TASKS_CC_VISION_CORE_BASE_VISION_TASK_API_FACTORY_H_

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "mediapipe/framework/calculator.pb.h"
#include "mediapipe/tasks/cc/core/task_api_factory.h"
#include "mediapipe/tasks/cc/core/task_runner.h"
#include "mediapipe/tasks/cc/vision/core/base_vision_task_api.h"
#include "tensorflow/lite/core/api/op_resolver.h"

namespace mediapipe {
namespace tasks {
namespace vision {
namespace core {

// Template creator for all subclasses of BaseVisionTaskApi.
class VisionTaskApiFactory {
 public:
  VisionTaskApiFactory() = delete;

  template <typename T>
  using EnableIfBaseVisionTaskApiSubclass = typename std::enable_if<
      std::is_base_of<BaseVisionTaskApi, T>::value>::type*;

  template <typename T, typename Options,
            EnableIfBaseVisionTaskApiSubclass<T> = nullptr>
  static absl::StatusOr<std::unique_ptr<T>> Create(
      CalculatorGraphConfig graph_config,
      std::unique_ptr<tflite::OpResolver> resolver, RunningMode running_mode,
      tasks::core::PacketsCallback packets_callback = nullptr,
      bool disable_default_service = false) {
    bool found_task_subgraph = false;
    for (const auto& node : graph_config.node()) {
      if (node.calculator() == "FlowLimiterCalculator") {
        continue;
      }
      if (found_task_subgraph) {
        return CreateStatusWithPayload(
            absl::StatusCode::kInvalidArgument,
            "Task graph config should only contain one task subgraph node.",
            MediaPipeTasksStatus::kInvalidTaskGraphConfigError);
      } else {
        MP_RETURN_IF_ERROR(
            tasks::core::TaskApiFactory::CheckHasValidOptions<Options>(node));
        found_task_subgraph = true;
      }
    }
    if (running_mode == RunningMode::LIVE_STREAM) {
      if (packets_callback == nullptr) {
        return CreateStatusWithPayload(
            absl::StatusCode::kInvalidArgument,
            "The vision task is in live stream mode, a user-defined result "
            "callback must be provided.",
            MediaPipeTasksStatus::kInvalidTaskGraphConfigError);
      }
    } else if (packets_callback) {
      return CreateStatusWithPayload(
          absl::StatusCode::kInvalidArgument,
          "The vision task is in image or video mode, a user-defined result "
          "callback shouldn't be provided.",
          MediaPipeTasksStatus::kInvalidTaskGraphConfigError);
    }
#if !MEDIAPIPE_DISABLE_GPU
    MP_ASSIGN_OR_RETURN(auto runner,
                        tasks::core::TaskRunner::Create(
                            std::move(graph_config), std::move(resolver),
                            std::move(packets_callback), nullptr, std::nullopt,
                            nullptr, std::nullopt, disable_default_service));
#else
    MP_ASSIGN_OR_RETURN(auto runner,
                        tasks::core::TaskRunner::Create(
                            std::move(graph_config), std::move(resolver),
                            std::move(packets_callback), nullptr, std::nullopt,
                            std::nullopt, disable_default_service));
#endif  // !MEDIAPIPE_DISABLE_GPU
    return std::make_unique<T>(std::move(runner), running_mode);
  }
};

}  // namespace core
}  // namespace vision
}  // namespace tasks
}  // namespace mediapipe

#endif  // MEDIAPIPE_TASKS_CC_VISION_CORE_BASE_VISION_TASK_API_FACTORY_H_
