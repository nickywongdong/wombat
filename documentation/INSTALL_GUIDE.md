# Installation Guide

## Installing Jetson TX2 Software
Ensure that the Jetson TX2 has been flashed with all options checked. L4T R28.1 is required at minimum.

Whilst logged into the `nvidia` profile of the Jetson:
1.  Run the following install scripts with sudo privileges:
    - In the `source/navigation/acm` directory, run: `sudo ./installCDCACM.sh`.
    - In the `source/install_tools` directory, run: `script`.
    - `sudo ./installdep.sh`. The Jetson will now reboot after this script has completed.
2.  Acquire the maps binary for your region [here](http://maps3.navit-project.org), and move the maps binary to the `~/axolotl/maps` folder on the Jetson (create any necessary directories that don't exist).

In Ubuntu system settings, set the `nvidia` profile to auto-login on boot. Additionally, add the `nvidia` user to the `sudoers` file, and ensure that `nvidia` gets no-password access to `sudo`.

## Installing Raspberry Pi Software
Only do the following if using Raspberry Pis that were not delivered with the project.

Whilst logged into the `pi` profile of Raspberry Pi:

1. Clone the repository in the home directory. The repository path should be: `/home/pi/wombat/`.
- Or, if setting up NOOBS on the Raspberry Pi, download the `rpidashcams` folder and save it to path `/home/pi/wombat/source/data_logging` (creating any directories that don't already exist).
2. Navigate to the `/source/data_logging/rpidashcams` directory and execute `make`.
3. Navigate to the `/home/pi/.config/autostart` directory and create the file: `axolotl_startup.desktop` (create any directories that don't already exist).
  - This file should contain the below:
    ```
    [Desktop Entry]
    Encoding=UTF-8
    Name=rpidcd
    Exec=lxterminal -e "/home/pi/wombat/source/data_logging/rpidashcams/rpiZdcd"
    Icon=lxterminal
    Type=Application
    Categories=Utility;
    ```
  - If the current Raspberry Pi is meant to be the front dashcam, change `rpiZdcd` in the exec line to: `rpi1dcd`.
  - If the current Raspberry Pi is meant to be the backup camera, change `rpiZdcd` in the exec line to: `rpi2dcd`.
4. Make the boot file executable using `chmod a+r /home/pi/.config/autostart/axolotl_startup.desktop`.
5. Open `/etc/wpa_supplicant/wpa_supplicant.conf`. Below `update_config=1`, remove any existing network configurations and add the following network configuration:
  ```
  network={
  	ssid="AxolotlWLAN"
  	psk="123123123"
  	key_mgmt=WPA-PSK
  }
  ````
6. Run `sudo reboot` on the Raspberry Pi.

Whilst logged into the `nvidia` profile of the Jetson:
1. Determine the Bluetooth address of each Raspberry Pi, and replace the Bluetooth addresses in `bluetooth_addresses` with those addresses.
`bluetooth_addresses` should only be comprised of two lines; the first with the Bluetooth address of the front Raspberry Pi, the second with the Bluetooth address of the rear Raspberry Pi.

## Backup Camera Integration
The system's backup camera is designed to turn on when gpio pin 298 (gpio298) is driven high (ideally, this uses a low-current and low-voltage line to reverse lights). If gpio298 is driven low, the backup camera will automatically turn off after 5 seconds.

## Deep Sleep / Auto Wake Integration
The system will automatically enter deep sleep when the gpio481 pin is driven high. To wake the system, simply touch the touchscreen.

__Note:__ Some unexpected behavior may occur during system sleep.

## For Fresh Installs
Before running a fresh installation of Axolotl, navigate to the `/home/nvidia/wombat/source/data_logging/wmanager` directory on the Jetson and execute `./set_ap_n`.

This only needs to be executed once; the Jetson will remember the settings for future boots.

## Camera Mounting
Each RaspberryPi should be connected to a USB power source that provides at least 5V and 1.2A. A 12V car adapter supplying 2.4A of current is recommended at minimum.

## Using External Storage
Axolotl is designed to be able to take advantage of external storage. A USB stick or SD card is recommended for this purpose.

When connecting an external storage device to the system, make sure the storage device is formatted in a format compatible with Ubuntu 16.04.

The storage device must be named `AXOLOTLDCV` (case-sensitive) and the user must be logged into the `nvidia` profile of the Jetson (the system will automatically scan for `/media/nvidia/AXOLOTLDCV`).

If an external drive is not detected, the system will resort to logging data onto internal storage.

__Note:__ as of the current build, Axolotl does not distinguish between multiple external storage drives with the name `AXOLOTLDCV`. For the most consistent logging performance, please only connect one external drive with the name `AXOLOTLDCV`.
