load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "grpc_client",
    srcs = [
        "grpc_client.cc",
    ],
    hdrs = [
        "grpc_client.h",
    ],
    linkopts = [
    ] + select({
        "//tools/platforms:x86_64": [
            "-lgrpc++",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//cyber",
        "//modules/v2x/common:v2x_proxy_gflags",
        "//modules/v2x/proto:v2x_service_car_to_obu_grpc",
    ] + select({
        "//tools/platforms:aarch64": [
            "@grpc_aarch64",
        ],
        "//conditions:default": [],
    }),
)

cc_library(
    name = "grpc_server",
    srcs = [
        "grpc_server.cc",
    ],
    hdrs = [
        "grpc_server.h",
    ],
    linkopts = [
    ] + select({
        "//tools/platforms:x86_64": [
            "-lgrpc++",
        ],
        "//conditions:default": [],
    }),
    deps = [
        "//cyber",
        "//modules/v2x/proto:v2x_service_obu_to_car_grpc",
    ] + select({
        "//tools/platforms:aarch64": [
            "@grpc_aarch64",
        ],
        "//conditions:default": [],
    }),
)

cc_test(
    name = "grpc_client_test",
    size = "small",
    srcs = [
        "grpc_client_test.cc",
    ],
    deps = [
        ":grpc_client",
        "@gtest//:main",
    ],
)

cc_test(
    name = "grpc_server_test",
    size = "small",
    srcs = [
        "grpc_server_test.cc",
    ],
    deps = [
        ":grpc_server",
        "@gtest//:main",
    ],
)

cpplint()
