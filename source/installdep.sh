#!/bin/bash

sudo apt-get update

sudo apt-get install build-essential cmake -y
sudo apt-get install build-essential zlib1g-dev -y
sudo apt-get install build-essential libpng12-dev -y
sudo apt-get install build-essential libgtk2.0-dev -y
sudo apt-get install build-essential librsvg2-bin -y
sudo apt-get install build-essential g++ -y
sudo apt-get install build-essential build-essential gpsd -y
sudo apt-get install build-essential gpsd-clients -y
sudo apt-get install build-essential libgps-dev -y
sudo apt-get install build-essential libdbus-glib-1-dev -y
sudo apt-get install build-essential libimlib2-dev -y
sudo apt-get install build-essential espeak -y

sudo apt-get install build-essential python -y
sudo apt-get install build-essential python-pip -y
sudo pip install --upgrade pip
sudo pip install obd

sudo apt-get install build-essential libboost-all-dev -y
sudo apt-get install build-essential libcrypto++ -y

sudo apt-get install build-essential libbluetooth-dev -y

cd acm/
sudo ./installCDCACM.sh

sudo apt-get install build-essential hostapd -y
sudo apt-get install build-essential dnsmasq -y

sudo apt-get install build-essential pulseaudio -y

sudo apt-get install build-essential gstreamer-0.10 -y
sudo apt-get install build-essential gstreamer0.10-plugins-good -y
sudo apt-get install build-essential gstreamer0.10-plugins-bad -y
sudo apt-get install build-essential gstreamer0.10-plugins-ugly -y

echo "Install script complete! Rebooting in 5 seconds..."

sleep 5s

sudo reboot
