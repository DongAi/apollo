load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "ncut",
    srcs = [
        "ncut.cc",
    ],
    hdrs = [
        "ncut.h",
    ],
    deps = [
        "//cyber",
        "//modules/perception/base",
        "//modules/perception/lidar/lib/segmentation/ncut/common:flood_fill",
        "//modules/perception/lidar/lib/segmentation/ncut/common:lr_classifier",
        "//modules/perception/lidar/lib/segmentation/ncut/proto:ncut_param_proto",
    ],
)

cc_library(
    name = "ncut_segmentation",
    srcs = [
        "ncut_segmentation.cc",
    ],
    hdrs = [
        "ncut_segmentation.h",
    ],
    copts = [
        "-fopenmp",
        #"-DDEBUG_NCUT",
    ],
    linkopts = [
        "-lgomp",
    ],
    deps = [
        ":ncut",
        "//cyber",
        "//modules/perception/base",
        "//modules/perception/lib/config_manager",
        "//modules/perception/lib/thread",
        "//modules/perception/lidar/common:pcl_util",
        "//modules/perception/lidar/lib/interface",
        "//modules/perception/lidar/lib/segmentation/ncut/common:flood_fill",
        "//modules/perception/lidar/lib/segmentation/ncut/common:lr_classifier",
        "//modules/perception/lidar/lib/segmentation/ncut/proto:ncut_param_proto",
        "@pcl",
        "@vtk",
    ],
)

cpplint()
