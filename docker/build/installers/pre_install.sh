#!/usr/bin/env bash

###############################################################################
# Copyright 2019 The Apollo Authors. All Rights Reserved.
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

# Install common tools.
apt-get update -y
apt-get install -y \
    apt-transport-https \
    build-essential \
    cmake \
    curl \
    software-properties-common \
    wget \
    unzip \
    zip \
    python \
    sudo \
    bc \
    cppcheck \
    debconf-utils \
    doxygen \
    graphviz \
    gdb \
    git \
    subversion \
    lcov \
    libblas-dev \
    libboost-all-dev \
    libcurl4-openssl-dev \
    libfreetype6-dev \
    liblapack-dev \
    libpcap-dev \
    locate \
    lsof \
    realpath \
    shellcheck \
    vim \
    v4l-utils \
    nfs-common \
    libatlas-base-dev \
    libnuma-dev \
    libncurses5 \
    libncurses5-dev \
    cmake \
    gcc \
    g++ \
    libleveldb-dev
