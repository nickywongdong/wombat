#!/bin/sh
make
sleep 5s

# sudo cp front_cam_autostart /etc/init.d/front_cam_autostart
# sudo chmod +x /etc/init.d/front_cam_autostart
# chdir /etc/init.d
# sudo update-rc.d front_cam_autostart defaults

sudo echo "sudo /home/pi/wombat/source/rpidashcams/rpi2dcd &" >> /etc/rc.local
sudo reboot