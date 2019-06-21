FROM arm64v8/ubuntu:14.04

ENV DEBIAN_FRONTEND=noninteractive

# Run installers.
COPY installers /tmp/installers
RUN bash /tmp/installers/pre_install.sh
RUN bash /tmp/installers/install_adolc_aarch64.sh
RUN bash /tmp/installers/install_adv_plat.sh
RUN bash /tmp/installers/install_bazel_aarch64.sh
RUN bash /tmp/installers/install_bazel_packages.sh
#RUN bash /tmp/installers/install_cuda_aarch64.sh
RUN bash /tmp/installers/install_fastrtps_aarch64.sh
RUN bash /tmp/installers/install_gflags_glog_aarch64.sh
RUN bash /tmp/installers/install_glew_aarch64.sh
RUN bash /tmp/installers/install_google_styleguide.sh
RUN bash /tmp/installers/install_gpu_caffe_aarch64.sh
RUN bash /tmp/installers/install_grpc_aarch64.sh
RUN bash /tmp/installers/install_ipopt_aarch64.sh
RUN bash /tmp/installers/install_libjsonrpc-cpp.sh
RUN bash /tmp/installers/install_nccl_aarch64.sh
RUN bash /tmp/installers/install_node_aarch64.sh
RUN bash /tmp/installers/install_osqp_aarch64.sh
RUN bash /tmp/installers/install_ota.sh
RUN bash /tmp/installers/install_pcl_aarch64.sh
RUN bash /tmp/installers/install_protobuf.sh
RUN bash /tmp/installers/install_python_modules.sh
RUN bash /tmp/installers/install_pytorch_aarch64.sh
RUN bash /tmp/installers/install_qp_oases.sh
RUN bash /tmp/installers/install_qt_aarch64.sh
RUN bash /tmp/installers/install_ros_aarch64.sh
RUN bash /tmp/installers/install_snowboy_aarch64.sh
RUN bash /tmp/installers/install_supervisor.sh
RUN bash /tmp/installers/install_undistort.sh
RUN bash /tmp/installers/install_user.sh
RUN bash /tmp/installers/install_yarn.sh
RUN bash /tmp/installers/post_install.sh

WORKDIR /apollo
