#!/usr/bin/env bash
make
sudo cp rear_cam_autostart /etc/init.d/rear_cam_autostart
chmod +x /etc/init.d/rear_cam_autostart
sleep 5s
sudo update-rc.d rear_cam_autostart defaults
sudo reboot
