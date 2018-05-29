#!/bin/bash

cd ../media_system/

# Install VLC
sudo apt-repository ppa:videolan/stable-daily
sudo apt-get update
sudo apt-get --assume-yes install vlc

# Install FM dependencies
# rtl_sdr and drivers for the USB FM Radio Receiver
git clone git://git.osmocom.org/rtl-sdr.git
cd rtl-sdr/
mkdir build
cd build
cmake ../ -DINSTALL_UDEV_RULES=ON
make
sudo make install
sudo ldconfig
sudo cp ../rtl-sdr.rules /etc/udev/rules.d/
#may need to blacklist driver dvb_usb_rtl128xxu

# Install GQRX
sudo apt-get --assume-yes gqrx-sdr

# Install bluetooth streaming
sudo apt-get --assume-yes install expect
