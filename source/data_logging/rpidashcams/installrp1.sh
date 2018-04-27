#!/bin/sh
make
sleep 5s

# sudo cp front_cam_autostart /etc/init.d/front_cam_autostart
# sudo chmod +x /etc/init.d/front_cam_autostart
# chdir /etc/init.d
# sudo update-rc.d front_cam_autostart defaults
sudo cp -n /etc/rc.local rc.local       # copy the original rc.local file here, but don't override it!
sudo cp rc.local /etc/rc.local          # copy the master copy of the rc.local file back into etc
sudo echo "sudo /home/pi/wombat/source/rpidashcams/rpi1dcd &" >> /etc/rc.local    # write our startup command into it
sudo reboot
