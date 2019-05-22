#!/usr/bin/env bash

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
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

ARCH=$(uname -m)

addgroup --gid "$DOCKER_GRP_ID" "$DOCKER_GRP"
adduser --disabled-password --force-badname --gecos '' "$DOCKER_USER" \
    --uid "$DOCKER_USER_ID" --gid "$DOCKER_GRP_ID" 2>/dev/null
usermod -aG sudo "$DOCKER_USER"
echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
cp -r /etc/skel/. /home/${DOCKER_USER}

if [ "$ARCH" == 'aarch64' ]; then
  echo "
export PATH=\$PATH:/usr/lib/java/bin:/apollo/scripts:/usr/local/miniconda2/bin/
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/lib:/usr/lib/aarch64-linux-gnu/tegra:/usr/local/ipopt/lib:/usr/local/cuda/lib64/stubs
export NVBLAS_CONFIG_FILE=/usr/local/cuda
if [ -e "/apollo/scripts/apollo_base.sh" ]; then 
  source /apollo/scripts/apollo_base.sh; 
fi
ulimit -c unlimited" >> /home/${DOCKER_USER}/.bashrc
  source /home/${DOCKER_USER}/.bashrc

#redirect libtorch on aarch64
sudo ln -s /usr/local/libtorch /usr/local/apollo/libtorch
else
  echo '
  export PATH=${PATH}:/apollo/scripts:/usr/local/miniconda2/bin
   if [ -e "/apollo/scripts/apollo_base.sh" ]; then
    source /apollo/scripts/apollo_base.sh
  fi
   ulimit -c unlimited
  ' >> "/home/${DOCKER_USER}/.bashrc"
fi

echo '
genhtml_branch_coverage = 1
lcov_branch_coverage = 1
' > "/home/${DOCKER_USER}/.lcovrc"

# Set user files ownership to current user, such as .bashrc, .profile, etc.
chown ${DOCKER_USER}:${DOCKER_GRP} /home/${DOCKER_USER}
ls -ad /home/${DOCKER_USER}/.??* | xargs chown -R ${DOCKER_USER}:${DOCKER_GRP}

# setup GPS device
if [ -e /dev/novatel0 ]; then
  chmod a+rw /dev/novatel0
fi
if [ -e /dev/novatel1 ]; then
  chmod a+rw /dev/novatel1
fi
if [ -e /dev/novatel2 ]; then
  chmod a+rw /dev/novatel2
fi

# setup camera device
if [ -e /dev/camera/obstacle ]; then
  chmod a+rw /dev/camera/obstacle
fi
if [ -e /dev/camera/trafficlights ]; then
  chmod a+rw /dev/camera/trafficlights
fi

if [ "$RELEASE_DOCKER" != "1" ];then
  # setup ros package
  # this is a temporary solution to avoid ros package downloading.
  ROS="/home/tmp/ros"
  chmod a+w "${ROS}/share/velodyne/launch/start_velodyne.launch"
  chmod a+w -R "${ROS}/share/velodyne_pointcloud/params"
fi
