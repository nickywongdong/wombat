# User Guide

## First Run
Before running Axolotl on the Jetson for the first time, navigate to the `/home/nvidia/wombat/source/data_logging/wmanager` directory and execute `./set_ap_n`.

This only needs to be executed once; the Jetson will remember the settings for future boots.

## Installation
### Installing Jetson TX2 Software
Whilst logged into the `nvidia` profile of the Jetson:
1.  Run the install script with sudo privileges: `sudo ./installdep.sh`. The Jetson will now reboot.
2.  In the `/acm` directory, and run: `sudo ./installCDCACM.sh`. Manually reboot the Jetson with `sudo reboot`.
3.  Download the maps binary [here](https://drive.google.com/open?id=1UpHisYQQdKC_r3oSZfjjtk_R77760Z-u), and move the maps binary to the `~/axolotl/maps` folder on the Jetson (create any necessary directories that don't exist).
5.  In the `source` directory, run `make fresh`.

### Installing Raspberry Pi Software
Whilst logged into the `pi` profile of Raspberry Pi:

1. Clone the repository in the home directory. The repository path should be: `/home/pi/wombat/`.
2. Navigate to the `/source/data_logging/rpidashcams` directory and execute `make`.
3. Navigate to the `/home/pi/.config/autostart` directory and create the file: `axolotl_startup.desktop` (create any directories that don't already exist too).
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
4. Open `/etc/wpa_supplicant/wpa_supplicant.conf`. Below `update_config=1`, ensure that the only network settings are:
  ```
  network={
  	ssid="AxolotlWLAN"
  	psk="123123123"
  	key_mgmt=WPA-PSK
  }
  ````
5. Run `sudo reboot` on the Raspberry Pi.

Whilst logged into the `nvidia` profile of the Jetson (only if using Raspberry Pis that were not shipped):
1. Determine the Bluetooth address of each Raspberry Pi, and replace the Bluetooth addresses in `bluetooth_addresses` with those addresses.
`bluetooth_addresses` should only be comprised of two lines; the first with the Bluetooth address of the front Raspberry Pi, the second with the Bluetooth address of the rear Raspberry Pi.

__Note:__ No more interaction is needed with the Raspberry Pi. The Raspberry Pi, on bootup, should be ready

## Backup Camera Integration
The system's backup camera is designed to turn on when gpio pin 298 (gpio298) is driven high. If gpio298 is driven low, the backup camera will automatically turn off after 5 seconds.

__Note:__ As of the current build, the system does not account for handling the backup camera for quick on-off cycles. For example, turning the backup camera on and off multiple times within 5 seconds may result in undesired behavior. Proceed with caution.

## Using External Storage
Axolotl is designed to be able to take advantage of external storage devices, either SD cards or USB drives that are compatible with the Jetson TX2.

When connecting an external storage device to the system, make sure the storage device is formatted in a Linux-compatible format.

The storage device must be named `AXOLOTLDCV` (case-sensitive) and the user must be logged into the `nvidia` profile of the Jetson (the system will automatically scan for `/media/nvidia/AXOLOTLDCV`).

If an external drive is not detected, the system will resort to logging data onto internal storage.

__Note:__ as of the current build, Axolotl does not distinguish between multiple external storage drives with the name `AXOLOTLDCV`. For the most consistent logging performance, please only connect one external drive with the name `AXOLOTLDCV`.

## FAQ
### Screen Turns Grey When Pairing with Bluetooth
This is perfectly normal behavior. The infotainment system will block and wait for you to connect your smartphone before any normal operations continue.
The infotainment system blocks for 10 seconds max before returning to normal.

## Known Bugs
### Dashcam Footage Disruptions
Dashcam footage may be corrupted if Axolotl is running and the system enters standby mode. For the best performance, close Axolotl before shutting entering standby mode.

### GPS Signal Loss
Mileage may vary depending on the GPS antenna used for the NEO M8U GPS chip.

### Raspberry Pi Cameras Fail to Connect
Raspberry Pis may boot slower than the Jetson; the Jetson may attempt to prematurely contact the Raspberry Pis and fail to detect them if Axolotl is launched before Raspberry Pi startup is finalized.
