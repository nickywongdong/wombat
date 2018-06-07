# User Guide

## Forewarning
Distracted driving may lead to accidents. Please obey all traffic laws and do not operate the system if system operation will affect your driving safety or the safety of other road users.

By continuing to use our system, you agree to these terms.

## Navigation
The navigation tab simply contains the Navit navigation system. This system functions similar to how Garmin navigation systems do.

By default, the map is displayed. Here, your route info as well as next turn instruction, GPS satellite strength, and true distance to destination is displayed. Pressing the __+__ or __-__ buttons will zoom the map in and out, respectively.

Pressing on the screen without moving will open the main menu.

Selecting __Go To__ will allow for address entry, previous destination entry, and the like. When entering a destination, tapping on the auto-completed suggestion will bring that selection up as a possible destination; tapping the checkbox to the right of the entry field will allow for further addresses to be entered.

Selecting __View Map__ will return you to the map interface.

Selecting __Settings__ will open a preferences menu that allows you to change navigation settings.

## Data
This tab allows the user to manage the data logging system.

__Clear logs__ enables the user to clear the data logs on the current logging volume by entering a password.

__Change password__ allows the user to change the password used to clear the data logs. The default password is `orangemonkeyeagle`; we strongly suggest changing this password to a more secure and personal password upon receipt of your system.

__Reset password__ resets the password to default.

__Note:__ Password entry for clear logs and change password is unavailable while the vehicle is moving.

## DTCs
This tab displays diagnostic trouble codes as well as the date/time of when the current diagnostic trouble codes were fetched. Diagnostic trouble codes are displayed as tuples that include the diagnostic trouble code itself as well as any information on that code found by python-OBD.

Selecting __Refresh__ will request new diagnostic trouble codes from the vehicle and update the display.

## Fuel Economy Analysis
This tab displays fuel economy data with respect to the current boot cycle (this may not encapsulate the entire driving cycle if Axolotl isn't started soon after vehicle start-up or shut-off).

Selecting __Refresh__ will re-run fuel economy analysis on the current boot cycle's OBD log and update the display.

## AHRS
This tab displays data from the AHRS sensor in an easily human-understandable format.

__Refresh__ will grab new readings from the sensor and display those.

__Zero__ calibrates the sensor; subsequent readings will be made with respect to the sensor's current orientation. Note that this does not affect the readings stored in the data log.

## Media
This tab displays media controls for auxiliary input, Bluetooth pairing, and volume settings.

__Aux__ will activate any Aux device connected to the Axolotl using the Aux dongle.

__Pair__ will block the system and allow you to connect a Bluetooth device for media playback. On the Bluetooth device you desire to connect, simply select "tegra-ubuntu"; the system should automatically connect to the device within 10 seconds.

__Audio Off__ will turn the audio system off. Turn the audio system on by adjusting the volume.

A volume slider is provided for adjusting master system output volume.

__Note:__ it may be more easier to have the Axolotl system volume maximized and instead adjust your car's audio output volume.

## FM
This tab displays the GQRX software radio.

The radio is turned on by pressing the power button in the upper left-hand corner of the screen.

Tapping on the individual digits at the top will adjust the current radio frequency. You may also drag the slider to change the frequency for finer tuning while driving.

GQRX supports many types of radio frequencies; you can adjust these by opening the "Mode" drop-down menu on the right-hand pane and selecting the desired radio mode. The default FM radio mode is `WFM (Stereo)`.

Radio data system data is not displayed by default. You may enable this functionality by tapping on the RDS checkbox while the RDS tab is selected in the lower right-hand corner.

## Media Player
This tab displays the VLC media player. Transport controls are located at bottom left; a dedicated volume slider for VLC output volume only is displayed at the bottom right.

__Note:__ it may be easier to adjust audio volume from the Media tab.

By default, VLC will display the `Music` folder at `/home/nvidia/Music`.

### Playing Media from External Storage
VLC will automatically display media on an external storage volume if there is one connected. Media on the external storage volume must be saved in a folder labeled `Music` folder at the base level of the external storage volume.

## FAQ
### Why does my screen turn grey when attempting to pair a Bluetooth device?
This is perfectly normal behavior. The infotainment system will block and wait for you to connect your smartphone before any normal operations continue.
The infotainment system will become responsive again after 10 seconds, regardless of whether a Bluetooth device is connected or not.

### Why are some segments of dashcam footage corrupt on system sleep/shutoff?
The current segment of dashcam footage may be corrupted if Axolotl is running and the system enters standby mode (negotiation with the dashcam logger does not occur on deep sleep).

### Why am I unable to get a fix with the GPS chip?
You're likely running on L4T R28.1, which requires the use of an experimental driver to enumerate the GPS chip. Upgrading to L4T R28.2 should solve this problem. Otherwise, check your GPS chip's connection.

### Why does my data log contain dashcam footage with no playable streams?
The Raspberry Pi camera controllers may have booted before the Jetson and were unable to connect to the Jetson's AP network to broadcast their stream. Cycling the power of the Raspberry Pis while the Jetson is on should alleviate the problem.

### Where is my master_log.csv?
A master data log with all AHRS data associated with the appropriate OBD time slots will only be assembled upon exiting Axolotl. Please close Axolotl using the X button and not attempting process kill from the command line by the `kill` command or otherwise.

### Why are OBD logs not being produced even with a Bluetooth dongle connected?
The OBD2 dongle may not be paired and connected correctly. Please try the connection using third-party OBD2 software ([OBD Auto Doctor](https://www.obdautodoctor.com/download?) is a good one). If the problem persists, please contact or submit an issue.

### Why do I not have an RDS option on the FM menu?
You may not have configured GQRX correctly. You can reconfigure GQRX from scratch by deleting the GQRX configuration file by executing `rm -f /home/nvidia/.config/gqrx/default.conf` from the terminal. Then, run GQRX on its own from the Ubuntu applications drawer. Once the antenna has been configured, navigate to the View menu and check RDS. Quit GQRX; settings should be saved for GQRX in Axolotl.
