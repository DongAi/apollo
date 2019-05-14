cc_library(
    name = "tensorrt",
    linkopts = [
        "-lnvcaffe_parser",
        "-L/usr/lib/aarch64-linux-gnu",
        "-lnvinfer",
        "-lnvinfer_plugin",
        "-lnvparsers",
    ],

    includes = [".","/usr/include/tensorrt",],
    visibility = ["//visibility:public"],
)

