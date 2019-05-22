package(default_visibility = ["//visibility:public"])

licenses(["notice"])

cc_library(
    name = "grpc_aarch64",
    copts = [
	"-I/usr/local/include/grpc",
	"-I/usr/local/include/grpc++",
	"-I/usr/local/include/grpcpp",
    ],
    linkopts = [
        "-L/usr/local/lib/grpc",
        "-lz",
        "-lssl",
        "-lgrpc",
        "-lgpr",
#        "-lgrpc++_cronet",
#        "-lgrpc++_error_details",
#        "-lgrpc++_reflection",
#        "-lgrpc++_unsecure",
        "-lgrpc++",
#        "-lgrpc_cronet",
#        "-lgrpc_plugin_support",
#        "-lgrpc_unsecure",
        "-lcrypto",
    ],
)
