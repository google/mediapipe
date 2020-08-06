# Copyright 2020 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("//mediapipe/framework/tool:mediapipe_graph.bzl", "mediapipe_simple_subgraph")
load("//mediapipe/framework/tool:mediapipe_graph.bzl", "mediapipe_binary_graph")

licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

mediapipe_binary_graph(
    name = "facial_search_cpu_binary",
    graph = "facial_search.pbtxt",
    output_name = "facial_search_cpu.binarypb",
    deps = [":cpu_calculators"],
)

mediapipe_binary_graph(
    name = "facial_search_gpu_binary",
    graph = "facial_search.pbtxt",
    output_name = "facial_search_gpu.binarypb",
    deps = [":gpu_calculators"],
)

graph_facial_search_deps = [
    "//mediapipe/calculators/core:flow_limiter_calculator",
    "//mediapipe/examples/facial_search/calculators:closest_embeddings_calculator",
]

cc_library(
    name = "cpu_calculators",
    deps = graph_facial_search_deps + [
        ":subgraph_face_detection_cpu",
        ":subgraph_face_embeddings_cpu",
    ],
)

cc_library(
    name = "gpu_calculators",
    deps = graph_facial_search_deps + [
        ":subgraph_face_detection_gpu",
        ":subgraph_face_embeddings_gpu",
    ] + [
        # Linux only.
        # Must have a GPU with EGL support:
        # ex: sudo aptitude install mesa-common-dev libegl1-mesa-dev libgles2-mesa-dev
        # (or similar nvidia/amd equivalent)
        "//mediapipe/gpu:gl_calculator_helper",
        "//mediapipe/gpu:gpu_buffer",
        "//mediapipe/gpu:gpu_shared_data_internal",
    ],
)

subgraph_face_detection_deps = [
    "//mediapipe/calculators/image:image_transformation_calculator",
    "//mediapipe/calculators/tflite:ssd_anchors_calculator",
    "//mediapipe/calculators/tflite:tflite_converter_calculator",
    "//mediapipe/calculators/tflite:tflite_inference_calculator",
    "//mediapipe/calculators/tflite:tflite_tensors_to_detections_calculator",
    "//mediapipe/calculators/util:detection_label_id_to_text_calculator",
    "//mediapipe/calculators/util:detection_letterbox_removal_calculator",
    "//mediapipe/calculators/util:non_max_suppression_calculator",
]

mediapipe_simple_subgraph(
    name = "subgraph_face_detection_cpu",
    graph = "subgraph_face_detection_cpu.pbtxt",
    register_as = "FaceDetectionSubgraph",
    deps = subgraph_face_detection_deps,
)

mediapipe_simple_subgraph(
    name = "subgraph_face_detection_gpu",
    graph = "subgraph_face_detection_gpu.pbtxt",
    register_as = "FaceDetectionSubgraph",
    deps = subgraph_face_detection_deps,
)

subgraph_face_embeddings_deps = [
    "//mediapipe/calculators/image:image_cropping_calculator",
    "//mediapipe/calculators/image:image_transformation_calculator",
    "//mediapipe/calculators/tflite:tflite_converter_calculator",
    "//mediapipe/calculators/tflite:tflite_inference_calculator",
    "//mediapipe/calculators/tflite:tflite_tensors_to_floats_calculator",
    "//mediapipe/calculators/util:detections_to_rects_calculator",
]

mediapipe_simple_subgraph(
    name = "subgraph_face_embeddings_cpu",
    graph = "subgraph_face_embeddings_cpu.pbtxt",
    register_as = "FaceEmbeddingsSubgraph",
    deps = subgraph_face_embeddings_deps,
)

mediapipe_simple_subgraph(
    name = "subgraph_face_embeddings_gpu",
    graph = "subgraph_face_embeddings_gpu.pbtxt",
    register_as = "FaceEmbeddingsSubgraph",
    deps = subgraph_face_embeddings_deps + [
        "//mediapipe/gpu:gpu_buffer_to_image_frame_calculator",
    ],
)
