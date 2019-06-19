#!/usr/bin/env bash

###############################################################################
# Copyright 2018 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

# Fail on first error.
set -e

# Install cuda8
wget http://182.61.33.235/download/apollo/apollo-docker/cuda8_cudnn6/cuda-repo-l4t-8-0-local_8.0.84-1_arm64.deb
dpkg -i cuda-repo-l4t-8-0-local_8.0.84-1_arm64.deb

# Install toolkit
apt-get update -y
apt-get -y install cuda-toolkit-8-0

#Install tensorrt
wget http://182.61.33.235/download/apollo/docker/nv-tensorrt-repo-ubuntu1604-rc-cuda8.0-trt3.0-20170922_3.0.0-1_arm64.deb
dpkg -i nv-tensorrt-repo-ubuntu1604-rc-cuda8.0-trt3.0-20170922_3.0.0-1_arm64.deb

apt-get update -y
apt-get install tensorrt -y

mkdir /usr/include/tensorrt
mv /usr/include/aarch64-linux-gnu/Nv* /usr/include/tensorrt/

# Install cudnn7
apt-get -y install libcudnn7 libcudnn7-dev

wget http://182.61.33.235/download/apollo/apollo-docker/nvblas.conf

mv nvblas.conf /usr/local/cuda/

ln -s /usr/local/cuda/lib64/stubs/libnvidia-ml.so /usr/local/cuda/lib64/stubs/libnvidia-ml.so.1


# Clean up.
rm -fr nv-tensorrt-repo-ubuntu1604-rc-cuda8.0-trt3.0-20170922_3.0.0-1_arm64.deb cuda-repo-l4t-8-0-local_8.0.84-1_arm64.deb
