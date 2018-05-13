# User Guide

## Installation
### Installing Jetson TX2 Software
Ensure that the Jetson TX2 has been flashed with all options checked. L4T R28.1 is required at minimum.

Whilst logged into the `nvidia` profile of the Jetson:
1.  Run the install script with sudo privileges: `sudo ./installdep.sh`. The Jetson will now reboot.
2.  In the `/acm` directory, and run: `sudo ./installCDCACM.sh`. Manually reboot the Jetson with `sudo reboot`.
3.  Download the maps binary [here](https://drive.google.com/open?id=1UpHisYQQdKC_r3oSZfjjtk_R77760Z-u), and move the maps binary to the `~/axolotl/maps` folder on the Jetson (create any necessary directories that don't exist).
5.  In the `source` directory, run `make fresh`.

### Installing Raspberry Pi Software (optional)
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

## First Run
Before running Axolotl on the Jetson for the first time, navigate to the `/home/nvidia/wombat/source/data_logging/wmanager` directory and execute `./set_ap_n`.

This only needs to be executed once; the Jetson will remember the settings for future boots.

## Using External Storage
Axolotl is designed to be able to take advantage of external storage devices, either SD cards or USB drives that are compatible with the Jetson TX2.

When connecting an external storage device to the system, make sure the storage device is formatted in a format compatible with Ubuntu 16.04.

The storage device must be named `AXOLOTLDCV` (case-sensitive) and the user must be logged into the `nvidia` profile of the Jetson (the system will automatically scan for `/media/nvidia/AXOLOTLDCV`).

If an external drive is not detected, the system will resort to logging data onto internal storage.

__Note:__ as of the current build, Axolotl does not distinguish between multiple external storage drives with the name `AXOLOTLDCV`. For the most consistent logging performance, please only connect one external drive with the name `AXOLOTLDCV`.

## FAQ
### Why does my screen turn grey when attempting to pair a Bluetooth device?
This is perfectly normal behavior. The infotainment system will block and wait for you to connect your smartphone before any normal operations continue.
The infotainment system will become responsive again after 10 seconds, regardless of whether a Bluetooth device is connected or not.

## Known Bugs
### Dashcam Footage Disruptions
The current segment of dashcam footage may be corrupted if Axolotl is running and the system enters standby mode. This will be addressed in future patches.

### I'm unable to get a fix with the GPS chip?
You're likely running on L4T R28.1, which requires the use of an experimental driver to enumerate the GPS chip. Upgrading to L4T R28.2 should solve this problem.

### Why do I keep getting corrupt non-playable dashcam footage?
This is largely due to the fact that the Raspberry Pis controlling the cameras boot at different times with respect to the Jetson, and fail to connect to the Jetson's AP network. This will be addressed in future patches. In the meantime, cycling the power of the Raspberry Pis while the Jetson is on should alleviate the problem.
