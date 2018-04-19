#!/usr/bin/env bash
make
sudo cp rear_cam_autostart /etc/init.d/rear_cam_autostart
sleep 5s
sudo chmod +x /etc/init.d/rear_cam_autostart
chdir /etc/init.d
sudo update-rc.d rear_cam_autostart defaults
sudo reboot
