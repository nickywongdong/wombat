# rpidashcams

Files in this directory are not used on the Jetson.

Instead, each RaspberryPi 3 and Camera Module V2 pair needs to have a copy of the repo at the `/source/` level saved `/home/pi/wombat/source`. Then, `chmod +x installrp1.sh` and `sudo ./installrpi1.sh` or `chmod +x installrp2.sh` and `sudo ./installrpi2.sh` needs to be called within `/home/pi/wombat/source/rpidashcams`.

## Notes
Each RaspberryPi should be connected to a USB power source that provides at least 5V and 1.2A. A 12V car adapter supplying 2.4A of current is recommended at minimum.
