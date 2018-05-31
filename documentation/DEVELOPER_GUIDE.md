# Developer Guide
This contains documentation regarding developing for Axolotl.

## Connectivity
Axolotl uses the Jetson's WiFi antennas to broadcast an 802.11n AP network at 2.4GHz; AP WiFi mode is __required__ for camera functionality. WiFi is managed by two scripts in the `source/data_logging/wmanager` directory: set_ap_n.sh and set_client.sh.

__set_ap_n.sh__ puts the Jetson in AP WiFi host mode, __set_client.sh__ puts the Jetson in default client mode. Only use __set_client.sh__ if wireless internet connection is desired for development/debugging. Otherwise, return the Jetson to host mode with __set_ap_n.sh__.

It may be easier to use a wired Ethernet connection and/or USB to SSH into the Jetson TX2 Development Kit for development.

## Data Logging System
### Daemon Manager
This subprogram manages the entire data logging subsystem of Axolotl. The daemon manager is forked and executed as a child process of main Qt UI process.

On execution, the daemon manager builds the black box directory for the current boot cycle and initializes the data logging and dashcam daemons.

After the daemons have been initialized, the daemon manager will act as backup camera manager, automatically turning the backup camera on or off based on the value of gpio298.

The daemon manager also kills the data logging and dashcam daemons properly upon exiting Axolotl, assembling the master_log.csv after both daemons have been successfully exited.

### Data Logging Daemon
This subprogram manages OBD2 and AHRS logging. The data logging daemon is forked and executed as a child process of the daemon manager process.

## Camera System Design
### Implemented
The Jetson broadcasts a 802.11n WiFi access point, and the cameras connect to it.

Camera RPi (client) >> 802.11n WiFi >> Jetson TX2 (host)

### Theoretical, Type 1
The cameras broadcast streams to the Jetson via peer-to-peer WiFi, leaving the Jetson free to connect to the internet via a smartphone hotspot, router, or modem.

Camera RPi >> P2P WiFi >> Jetson TX2 >> Smartphone/Router/Modem >> Internet

### Theoretical, Type 2
The Jetson broadcasts a 802.11n WiFi access point, and the cameras connect to it. The Jetson connects to the Internet via a LTE modem connected over PCIe or a secondary WiFi adapter connected via Ethernet or USB, sharing the connection with the camera modules.

Camera RPi (client) << 802.11n WiFi >> Jetson TX2 (host) >> LTE Modem/Secondary WiFi Adapter >> Internet

__Note:__ This may address clock skew between the Raspberry Pis and the Jetson, reducing the latency of the camera streams.
