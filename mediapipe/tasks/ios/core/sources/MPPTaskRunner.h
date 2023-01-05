// Copyright 2022 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import <Foundation/Foundation.h>

#include "mediapipe/framework/calculator.pb.h"
#include "mediapipe/tasks/cc/core/task_runner.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * This class is used to create and call appropriate methods on the C++ Task Runner to initialize,
 * execute and terminate any Mediapipe task. 
 * 
 * An instance of the newly created C++ task runner will
 * be stored until this class is destroyed. When methods are called for processing (performing
 * inference), closing etc., on this class, internally the appropriate methods will be called on the
 * C++ task runner instance to execute the appropriate actions. For each type of task, a subclass of
 * this class must be defined to add any additional functionality. For eg:, vision tasks must create
 * an `MPPVisionTaskRunner` and provide additional functionality. An instance of
 * `MPPVisionTaskRunner` can in turn be used by the each vision task for creation and execution of
 * the task. Please see the documentation for the C++ Task Runner for more details on how the taks
 * runner operates.
 */
@interface MPPTaskRunner : NSObject

/**
 * Initializes a new `MPPTaskRunner` with the mediapipe task graph config proto and an optional C++
 * packets callback. 
 * 
 * You can pass `nullptr` for `packetsCallback` in case the mode of operation
 * requested by the user is synchronous. 
 * 
 * If the task is operating in asynchronous mode, any iOS Mediapipe task that uses the `MPPTaskRunner` 
 * must define a C++ callback function to obtain the results of inference asynchronously and deliver
 * the results to the user. To accomplish this, callback function will in turn invoke the block 
 * provided by the user in the task options supplied to create the task. 
 * Please see the documentation of the C++ Task Runner for more information on the synchronous and 
 * asynchronous modes of operation.
 *
 * @param graphConfig A mediapipe task graph config proto.
 *
 * @param packetsCallback An optional C++ callback function that takes a list of output packets as
 * the input argument. If provided, the callback must in turn call the block provided by the user in
 * the appropriate task options.
 *
 * @return An instance of `MPPTaskRunner` initialized to the given graph config proto and optional
 * packetsCallback.
 */
- (instancetype)initWithCalculatorGraphConfig:(mediapipe::CalculatorGraphConfig)graphConfig
                              packetsCallback:
                                  (mediapipe::tasks::core::PacketsCallback)packetsCallback
                                        error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/** A synchronous method for processing batch data or offline streaming data. This method is
designed for processing either batch data such as unrelated images and texts or offline streaming
data such as the decoded frames from a video file and an audio file. The call blocks the current
thread until a failure status or a successful result is returned. If the input packets have no
timestamp, an internal timestamp will be assigend per invocation. Otherwise, when the timestamp is
set in the input packets, the caller must ensure that the input packet timestamps are greater than
the timestamps of the previous invocation. This method is thread-unsafe and it is the caller's
responsibility to synchronize access to this method across multiple threads and to ensure that the
input packet timestamps are in order.*/
- (absl::StatusOr<mediapipe::tasks::core::PacketMap>)process:
    (const mediapipe::tasks::core::PacketMap &)packetMap;

/** Shuts down the C++ task runner. After the runner is closed, any calls that send input data to
 * the runner are illegal and will receive errors. */
- (absl::Status)close;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
