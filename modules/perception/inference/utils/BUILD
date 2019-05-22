load("//tools:cpplint.bzl", "cpplint")
load("//tools:cuda_library.bzl", "cuda_library")

package(default_visibility = ["//visibility:public"])

cuda_library(
    name = "inference_util_cuda_lib",
    srcs = [
        "util.cu",
        "cuda_util.cu",
        "resize.cu",
        "gemm.cu",
        "roipooling_layer.cu",
    ],
    hdrs = [
        "util.h",
        "cuda_util.h",
        "resize.h",
        "gemm.h",
        "roipooling_layer.h",
    ],
    deps = [
        "//cyber",
        "//modules/perception/inference:layer_lib",
        "@cuda",
        "@eigen",
    ],
)

cc_library(
    name = "inference_util_lib",
    srcs = [
        "util.cc",
        "roipooling_layer.cc",
        ":inference_util_cuda_lib",
    ],
    hdrs = [
        "util.h",
        "cuda_util.h",
        "resize.h",
        "gemm.h",
        "roipooling_layer.h",
    ],
    linkopts = ["-lopencv_core -lopencv_imgproc -lopencv_highgui -lnvinfer_plugin"],
    linkstatic = 1,
    deps = [
        "//modules/perception/base:blob",
        "//modules/perception/base:box",
        "//modules/perception/base:image",
        "//modules/perception/base:point_cloud",
        "//modules/perception/inference:layer_lib",
        "@caffe",
    ],
)

cc_test(
    name = "inference_util_test",
    size = "small",
    srcs = ["util_test.cc"],
    data = [
        "//modules/perception/inference:inference_test_data",
    ],
    deps = [
        ":inference_util_lib",
        "@gtest//:main",
    ],
)

cc_library(
    name = "inference_binary_data_lib",
    srcs = [
        "binary_data.cc",
    ],
    hdrs = ["binary_data.h"],
    linkopts = ["-lopencv_core -lopencv_imgproc -lopencv_highgui -lnvinfer_plugin"],
    deps = [
        "//modules/perception/base:blob",
        "@caffe",
    ],
)

cc_test(
    name = "inference_binary_data_test",
    size = "small",
    srcs = ["binary_data_test.cc"],
    data = [
        "//modules/perception/inference:inference_test_data",
    ],
    deps = [
        ":inference_binary_data_lib",
        "@gtest//:main",
    ],
)

cpplint()
