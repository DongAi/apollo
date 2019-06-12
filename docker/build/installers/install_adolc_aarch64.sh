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

cd "$(dirname "${BASH_SOURCE[0]}")"

sudo apt-get install autoconf automake libtool

wget http://182.61.33.235/download/apollo/ApolloAuto/libs/adolc.zip
#wget http://www.baiduapollo.club/download/apollo/ApolloAuto/libs/adolc.zip

sudo unzip adolc.zip -d /usr/local/

export LD_LIBRARY_PATH=/usr/local/adolc/lib64:$LD_LIBRARY_PATH 

# Clean up.
sudo rm -fr adolc.zip
