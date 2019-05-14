package(default_visibility = ["//visibility:public"])

licenses(["notice"])



cc_library(
    name = "cuda",
    includes = [
        "include",
    ],
    copts = [
	"-I/usr/local/cuda/targets/aarch64-linux/include",
	"-I/usr/local/cuda/extras/CUPTI/include",
	"-I/usr/local/cuda/targets/aarch64-linux/include",
	"-I/usr/local/cuda/nvvm/include",
    ],
    linkopts = [
	"-L/usr/lib/x86_64-linux-gnu/",
        "-L/usr/lib/aarch64-linux-gnu/",
        "-lgomp",
        "-L/usr/local/cuda/lib64",
        "-lOpenCL",
        "-lcublas",
        "-lcudart",
        "-lcudnn",
        "-lcufft",
        "-lcufftw",
        "-lcuinj64",
        "-lcurand",
        "-lcusolver",
        "-lcusparse",
        "-lnppc",
        "-lnppi",
        "-lnppial",
        "-lnppicc",
        "-lnppicom",
        "-lnppidei",
        "-lnppif",
        "-lnppig",
        "-lnppim",
        "-lnppist",
        "-lnppisu",
        "-lnppitc",
        "-lnpps",
        "-lnvToolsExt",
        "-lnvblas",
        "-lnvgraph",
        "-lnvrtc-builtins",
        "-lnvrtc",
        "-L/usr/local/cuda/lib64/stubs",
        "-lcublas",
        "-lcuda",
        "-lcufft",
        "-lcufftw",
        "-lcurand",
        "-lcusolver",
        "-lcusparse",
        "-lnppc",
        "-lnppi",
        "-lnppial",
        "-lnppicc",
        "-lnppicom",
        "-lnppidei",
        "-lnppif",
        "-lnppig",
        "-lnppim",
        "-lnppist",
        "-lnppisu",
        "-lnppitc",
        "-lnpps",
        "-lnvgraph",
        "-lnvidia-ml",
        "-lnvrtc",
    ],
)
