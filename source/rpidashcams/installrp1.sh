#!/usr/bin/env bash
make
sudo cp front_cam_autostart /etc/init.d/front_cam_autostart
sleep 5s
sudo update-rc.d front_cam_autostart defaults
sudo reboot
