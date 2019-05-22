load("//tools:cpplint.bzl", "cpplint")
load("//tools:cuda_library.bzl", "cuda_library")

package(default_visibility = ["//visibility:public"])

#cuda_library(
#    name = "similar_cuda",
#    srcs = [
#        "similar.cu",
#    ],
#    hdrs = [
#        "similar.h",
#    ],
#    deps = [
#        "//cyber",
#        "//modules/perception/camera/common:camera_frame",
#        "//modules/perception/inference/utils:inference_util_lib",
#        "@cuda",
#    ],
#)
#
#cc_library(
#    name = "similar",
#    srcs = [
#        "similar.cc",
#        ":similar_cuda",
#    ],
#    hdrs = [
#        "similar.h",
#    ],
#    deps = [
#        "//modules/perception/base",
#        "//modules/perception/camera/common",
#        "@eigen",
#    ],
#)

cc_library(
    name = "half_circle_angle",
    srcs = [
        "half_circle_angle.cc",
    ],
    hdrs = [
        "half_circle_angle.h",
    ],
    deps = [
        "//modules/perception/camera/common",
    ],
)

cc_library(
    name = "kalman_filter",
    srcs = [
        "kalman_filter.cc",
    ],
    hdrs = [
        "kalman_filter.h",
    ],
    deps = [
        "//cyber",
        "@eigen",
    ],
)

cc_library(
    name = "common",
    deps = [
        ":half_circle_angle",
        ":kalman_filter",
        ":region_output",
    ],
)

cuda_library(
    name = "region_output_cuda",
    srcs = [
        "region_output.cu",
        "similar.cu",
    ],
    hdrs = [
        "region_output.h",
        "similar.h",
    ],
    deps = [
        ":object_maintainer",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/inference/utils:inference_util_lib",
        "//modules/perception/camera/lib/obstacle/detector/yolo/proto:yolo_proto",
        "@cuda",
    ],
)

cc_binary(
    name = "libregion_cuda_test.so",
    srcs = [
        "main.cc",
    ],
    linkshared = True,
    linkstatic = False,
    deps = [
#        "//modules/perception/onboard/component:perception_component_inner_camera",
        "//cyber",
#        "//modules/perception/base",
#        "//modules/perception/camera/common",
#        "//modules/perception/camera/lib/interface",
#        "//modules/perception/camera/lib/lane/common:denseline_proto",
#        "//modules/perception/inference:inference_factory_lib",
#        "//modules/perception/inference/tensorrt:rt_net",
#        "//modules/perception/inference/tensorrt:rt_utils",
#        "//modules/perception/inference/tensorrt/plugins:perception_inference_tensorrt_plugins_softmax",
#        "//modules/perception/inference/tensorrt/plugins:perception_inference_tensorrt_plugins_argmax",
        ":main_lib",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/camera/lib/obstacle/detector/yolo/proto:yolo_proto",
        "//modules/perception/inference/utils:inference_util_lib",
#        "//modules/perception/camera/lib/obstacle/tracker/common:similar",
        "//modules/perception/inference/tensorrt/plugins:perception_inference_tensorrt_plugins",
#        ":region_output",
#        "@eigen",
    ],
)

cc_library(
    name = "main_lib",
    hdrs = [
        "main.h"
    ],
)

cc_library(
    name = "region_output",
    srcs = [
        "region_output.cc",
        "similar.cc",
        ":region_output_cuda",
    ],
    hdrs = [
        "region_output.h",
        "similar.h",
        "main.h"
    ],
    linkstatic = True,
    deps = [
        "//cyber",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/camera/lib/obstacle/detector/yolo/proto:yolo_proto",
    ],
)

cc_library(
    name = "yolo_obstacle_detector",
    srcs = [
        "yolo_obstacle_detector.cc",
    ],
    hdrs = [
        "yolo_obstacle_detector.h",
    ],
    deps = [
        ":region_output",
        "//cyber/common:file",
        "//modules/perception/base",
        "//modules/perception/camera/common",
        "//modules/perception/camera/lib/feature_extractor/tfe:external_feature_extractor",
        "//modules/perception/camera/lib/feature_extractor/tfe:project_feature",
        "//modules/perception/camera/lib/feature_extractor/tfe:tracking_feat_extractor",
        "//modules/perception/camera/lib/interface",
        "//modules/perception/camera/lib/obstacle/detector/yolo/proto:yolo_proto",
        "//modules/perception/inference:inference_factory_lib",
        "//modules/perception/inference:inference_lib",
        "//modules/perception/inference/utils:inference_util_lib",
        "//modules/perception/lib/utils",
    ],
)

cc_library(
    name = "object_maintainer",
    hdrs = [
        "object_maintainer.h",
    ],
    deps = [
        "//modules/perception/base",
    ],
)

cpplint()
