# Installation Guide

## Jetson TX2
Ensure that the Jetson TX2 has been flashed with all options checked. L4T R28.1 is required at minimum.

Whilst logged into the `nvidia` profile of the Jetson:
1.  Clone this repository in the home directory. The repository path should be: `/home/nvidia/wombat/`.
2.  `cd` into the home directory and make all scripts executable using `find ./ -name "*.sh" -exec chmod +x {} \;`.
3.  Run the following install scripts with sudo privileges:
    - In the `source/navigation/acm` directory, run: `sudo ./installCDCACM.sh`.
    - In the `source/install_tools` directory, run: `sudo ./installdep_media.sh`, `sudo ./installdep_ui.sh`, and `sudo ./installdep_data.sh`. The Jetson will now reboot after `installdep_data.sh` has finished executing.
4.  Build the infotainment system by navigating into the `source/install_tools` directory and running `sudo ./install_builder.sh`.
5.  Acquire the maps binary for your region [here](http://maps3.navit-project.org). Name this binary `namaps.bin` and move the maps binary to the `/home/nvidia/axolotl/maps` folder on the Jetson (create any intermediate directories that don't exist).

In Ubuntu system settings, set the `nvidia` profile to auto-login on boot. Additionally, add the `nvidia` user to the `sudoers` file, and ensure that `nvidia` gets no-password access to `sudo`.

## Raspberry Pi
Only do the following if using Raspberry Pis that were not delivered with the project.

Whilst logged into the `pi` profile of Raspberry Pi:

1. Clone this repository in the home directory. The repository path should be: `/home/pi/wombat/`.
- Or, if setting up NOOBS on the Raspberry Pi, download the `rpidashcams` folder and save it to path `/home/pi/wombat/source/data_logging` (creating any directories that don't already exist).
2. Navigate to the `/source/data_logging/rpidashcams` directory and execute `make`.
3. Navigate to the `/home/pi/.config/autostart` directory and create the file: `axolotl_startup.desktop` (create any directories that don't already exist).
  - This file should contain the below:
    ```
    [Desktop Entry]
    Encoding=UTF-8
    Name=rpidcd
    Exec=lxterminal -e "/home/pi/wombat/source/data_logging/rpidashcams/rpi#dcd"
    Icon=lxterminal
    Type=Application
    Categories=Utility;
    ```
  - If the current Raspberry Pi is meant to be the front dashcam, change `#` in the exec line to: `1` (i.e. `rpi1dcd`).
  - If the current Raspberry Pi is meant to be the backup camera, change `#` in the exec line to: `2` (i.e. `rpi2dcd`)..
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
1. Determine the MAC address of each Raspberry Pi, and replace the first two MAC addresses in `bluetooth_addresses` with those addresses.

## For Fresh Installs
Before running a fresh installation of Axolotl, navigate to the `/home/nvidia/wombat/source/data_logging/wmanager` directory on the Jetson and execute `sudo ./set_ap_n`.

This only needs to be executed once; the Jetson will remember the settings for future boots.

## OBD Integration
Only do the following if using a different Bluetooth dongle than the one delivered with the project.

Whilst logged into the `nvidia` profile of the Jetson:
1. Determine the MAC address of the Bluetooth dongle and replace the third MAC address in `bluetooth_addresses` with that address.

__Note:__ OBDLink MX Bluetooth dongle is recommended.

## Backup Camera Integration
The system's backup camera is designed to turn on when gpio298 is driven high (ideally, this uses a low-current and low-voltage line to reverse lights). If gpio298 is driven low, the backup camera will automatically turn off after 5 seconds.

## Deep Sleep / Auto Wake Integration
The system will automatically enter deep sleep when the gpio481 pin is driven high. To wake the system, simply touch the touchscreen.

__Note:__ Some unexpected behavior may occur during system sleep.

## Camera Mounting
Each RaspberryPi should be connected to a USB power source that provides at least 5V and 1.2A. A 12V car adapter supplying 2.4A of current is recommended at minimum.

## Using External Storage
USB drives or SD cards are recommended for external storage. When connecting an external storage device to the system, make sure the storage device is formatted in a format compatible with Ubuntu 16.04.

The storage device must be named `AXOLOTLDCV` (case-sensitive) and the user must be logged into the `nvidia` profile of the Jetson. The system will automatically scan for the flash drive and use it for data logging if connected.

If an external drive is not detected, the system will resort to logging data onto internal storage.

__Warning:__ The system will automatically delete older logs to make space for newer logs if storage space is low on the internal storage volume (this does not apply if using external storage).

__Note:__ For the most consistent logging performance, please only connect one external drive with the name `AXOLOTLDCV`.
