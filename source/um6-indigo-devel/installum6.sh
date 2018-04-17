#!/bin/bash

sudo apt-get install ros-kinetic-catkin -y
source /opt/ros/kinetic/setup.bash
cmake CMakeLists.txt
make
