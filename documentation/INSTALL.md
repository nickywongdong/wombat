# Installing Navigation and Data logging

Installing Jetson TX2 Software:
1.  Run the install script with sudo privileges: `sudo ./installdep.sh`. The Jetson will now reboot.
2.  In the `/acm` directory, and run: `sudo ./installCDCACM.sh`. Manually reboot the Jetson with `sudo reboot`.
3.  Download the maps binary [here](https://drive.google.com/open?id=1UpHisYQQdKC_r3oSZfjjtk_R77760Z-u), and move the maps binary to the `~/axolotl/maps` folder on the Jetson (create any necessary directories that don't exist).
5.  In the `source` directory, run `make fresh`.

Installing RaspberryPi Software:
1. Copy the `/rpidashcams` folder onto the home directory and run the `installrpi1.sh` script on the RaspberryPi desired for the front camera, then run `installrpi2.sh` on the RaspberryPi desired for the rear camera/backup camera.
2. Required for using RaspberryPis that were not shipped: Determine the Bluetooth address of each RaspberryPi, and replace the Bluetooth addresses in `macaddrs` with those addresses. `macaddrs` should only be comprised of two lines; the first with the Bluetooth address of the front RaspberryPi, the second with the Bluetooth address of the rear RaspberryPi.
