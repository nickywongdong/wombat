# User Guide

## Installation
### Installing Jetson TX2 Software
1.  Run the install script with sudo privileges: `sudo ./installdep.sh`. The Jetson will now reboot.
2.  In the `/acm` directory, and run: `sudo ./installCDCACM.sh`. Manually reboot the Jetson with `sudo reboot`.
3.  Download the maps binary [here](https://drive.google.com/open?id=1UpHisYQQdKC_r3oSZfjjtk_R77760Z-u), and move the maps binary to the `~/axolotl/maps` folder on the Jetson (create any necessary directories that don't exist).
5.  In the `source` directory, run `make fresh`.

### Installing RaspberryPi Software
1. Navigate to the `/rpidashcams` directory and follow installation instructions for each RaspberryPi.
2. If using RaspberryPis that were not shipped with Jetson:
- Determine the Bluetooth address of each RaspberryPi, and replace the Bluetooth addresses in `macaddrs` with those addresses. `macaddrs` should only be comprised of two lines; the first with the Bluetooth address of the front RaspberryPi, the second with the Bluetooth address of the rear RaspberryPi.

## Using External Storage
Axolotl is designed to be able to take advantage of external storage devices, either SD cards or USB drives of any type.

When connecting an external storage device to the system, make sure the storage device is formatted in a Linux-compatible format.

The storage device must be named `AXOLOTLDCV` (case-sensitive) and the user must be logged into the `nvidia` profile of the Jetson (the system will automatically scan for `/media/nvidia/AXOLOTLDCV`).

If an external drive is not detected, the system will resort to logging data onto internal storage.

Note: as of the current build, Axolotl does not distinguish between multiple external storage drives with the name `AXOLOTLDCV`. For the most consistent logging performance, please only connect one external drive with the name `AXOLOTLDCV`.
