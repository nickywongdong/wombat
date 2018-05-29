#!/bin/bash

# Only run this after all dependencies have been installed!

# Build AHRS logger
echo "Building AHRS logger..."
cd $PWD/../data_logging/um6
sleep 1s
cmake CMakeLists.txt
sleep 1s
make
sleep 1s
if [ ! -f /imu ]; then
  echo "AHRS build: [[ FAILED ]]."
else
  echo "AHRS build: [[ SUCCEEDED ]]."

# Build the rest of the data logging system
TOTAL=0
cd $PWD/../data_logging
sleep 1s
make -f makefile.data_logging

if [ -f /daemon_launcher ]; then
  TOTAL=TOTAL+1
fi

if [ -f /datad ]; then
  TOTAL=TOTAL+1
fi

if [ -f /datad_pyhelper ]; then
  TOTAL=TOTAL+1
fi

if [ -f /dashcamd ]; then
  TOTAL=TOTAL+1
fi

if [ -f /record_helper ]; then
  TOTAL=TOTAL+1
fi

if [ -f /backup_cam_helper ]; then
  TOTAL=TOTAL+1
fi

if [[ $TOTAL == 6]] then
  echo "Data Logging system build: [[ SUCCESSFUL ]]"
else
  echo "Data Logging system build: [[ FAILED ]]"
fi
cd ..

# Build QT
# Run Qmake
cd $PWD/..
mkdir axolotl_build
cd axolotl_build
qmake $PWD/../Axolotl1.1/axolotl.pro

# Make UI executable
make -f Makefile

# Symlink executable with desktop file
touch $HOME/Desktop/Axolotl
ln -s $HOME/Desktop/Axolotl Axolotl

# Build switch toggle
cd ..
cd sleep_mode
make -f Makefile

echo "Axolotl has been built. Rebooting in 5 seconds..."
sleep 5s
sudo reboot
