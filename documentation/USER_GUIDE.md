# User Guide

## Navigation
The navigation tab simply contains the Navit navigation system. This system functions similar to how Garmin navigation systems do.

By default, the map is displayed. Here, your route info as well as next turn instruction, GPS satellite strength, and true distance to destination is displayed. Pressing the + or - buttons will zoom the map in and out, respectively.

Pressing on the screen without moving will open the main menu. Selecting __Go To__ will allow for address entry, previous destination entry, and the like. Selecting __View Map__ will return you to the map interface. Selecting __Settings__ will open a preferences menu that allows you to change navigation settings.

## Data
Data functionality is encapsulated within the "Data Logging", "AHRS", and "Fuel Economy Analysis" tabs.

### Data Logging
This tab allows the user to manage the data logging system.

__Clear logs__ enables the user to clear the data logs on the current logging volume by entering a password.

__Change password__ allows the user to change the password used to clear the data logs. The default password is `orangemonkeyeagle`; we strongly suggest changing this password to a more secure and personal password upon receipt of your system.

__Reset password__ resets the password to default. In future patches, this will require a reset code shipped with the system.

### AHRS
This tab displays data from the AHRS sensor in an easily human-understandable format.

__Refresh__ will grab new readings from the sensor and display those.
__Zero__ calibrates the sensor; subsequent readings will be made with respect to the sensor's current orientation. Note that this does not affect the readings stored in the data log.

### Fuel Economy Analysis
To be added!

## FAQ
### Why does my screen turn grey when attempting to pair a Bluetooth device?
This is perfectly normal behavior. The infotainment system will block and wait for you to connect your smartphone before any normal operations continue.
The infotainment system will become responsive again after 10 seconds, regardless of whether a Bluetooth device is connected or not.

### Why are some segments of dashcam footage corrupt on system sleep/shutoff?
The current segment of dashcam footage may be corrupted if Axolotl is running and the system enters standby mode (negotiation with the dashcam logger does not occur on deep sleep). This will be addressed in future patches.

### Why am I unable to get a fix with the GPS chip?
You're likely running on L4T R28.1, which requires the use of an experimental driver to enumerate the GPS chip. Upgrading to L4T R28.2 should solve this problem. Otherwise, check your GPS chip's connection.

### Why does my data log contain dashcam footage with no playable streams?
The Raspberry Pi camera controllers may have booted before the Jetson and were unable to connect to the Jetson's AP network to broadcast their stream. Cycling the power of the Raspberry Pis while the Jetson is on should alleviate the problem.
