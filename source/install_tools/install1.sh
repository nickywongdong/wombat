#!/bin/bash

# Build AHRS logger
cd $PWD/../data_logging/um6
sleep 1s
cmake CMakeLists.txt
sleep 1s
make
sleep 1s

# Build the rest of the data logging system
cd $PWD/../data_logging
sleep 1s
make -f makefile.data_logging
sleep 1s
cd ..
sleep 1s
