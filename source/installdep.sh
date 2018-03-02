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
sudo apt-get install espeak -y

sudo acm/installCDCACM.sh

sudo apt-get install build-essential hostapd -y
sudo apt-get install build-essential dnsmasq -y

sudo apt-get install build-essential pulseaudio -y

sudo reboot
