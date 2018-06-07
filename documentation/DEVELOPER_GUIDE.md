# Developer Guide
Axolotl is a completely modular system, with the user interface, data logging system, and media subsystem each managing their own modular components.

## Connectivity
Axolotl uses the Jetson's WiFi antennas to broadcast an 802.11n AP network at 2.4GHz; AP WiFi mode is __required__ for camera functionality. WiFi is managed by two scripts in the `source/data_logging/wmanager` directory: `set_ap_n.sh` and `set_client.sh`.

Similarly, the Raspberry Pis controlling the camera modules __must__ be connected to the Jetson's AP network to broadcast their streams. The WiFi __must__ connect before streams are started, otherwise corrupt dashcam footage and backup camera feeds may result.

`set_ap_n.sh` puts the Jetson in AP WiFi host mode, `set_client.sh` puts the Jetson in default client mode. Only use `set_client.sh` if wireless internet connection is desired for development/debugging. Otherwise, return the Jetson to host mode with `set_ap_n.sh`.

__Note:__ It may be easier to use a wired Ethernet connection and/or USB to SSH into the Jetson TX2 Development Kit and/or the Raspberry Pis for development.

### LTE
LTE remains a connectivity option that may be desirable. Use of a Huawei LTE modem connected to the Jetson via Mini-PCIe Express combined with a prepaid US Mobile SIM for IoT devices was considered but not implemented. Adding LTE support may alleviate camera streaming issues due to clock skew between the Jetson and the Raspberry Pis.

## Data Logging System
### Daemon Manager (`daemon_manager.cpp` and `daemon_manager`)
This subprogram manages the entire data logging subsystem of Axolotl. The daemon manager is forked and executed as a child process of main Qt UI process.

On execution, the daemon manager builds the black box directory for the current boot cycle and initializes the data logging and dashcam daemons.

After the daemons have been initialized, the daemon manager will act as backup camera manager, automatically turning the backup camera on or off based on the value of gpio298 (1 = on, 0 = off).

The daemon manager also kills the data logging and dashcam daemons properly upon exiting Axolotl, assembling the master_log.csv after both daemons have been successfully exited.

### Data Logging Daemon (`data_logger.cpp` and `datad`)
This program manages OBD2 and AHRS logging. The data logging daemon is forked and executed as a child process of the daemon manager process.

#### `data_obd_logger.py`
This script handles all OBD2 logging. Recompilation is not required after modifying this script.

#### `data_obd_dtc.py`
This script handles fetching DTC data from the OBD2 port. Recompilation is not required after modifying this script.

### Data Collator (`data_collator.py`)
This script handles the collation of data logs after Axolotl exit. Upon exiting Axolotl by tapping the red X, the Data Collator script will scan for an OBD2 log, and then append AHRS data to each line with the corresponding timestamp, producing a `master_log.csv`. This script will only correctly output `master_log.csv` if there is an `obd_log.csv` file in the current logging directory.

### Dashcam Logging Daemon (`dashcam_logger.cpp` and `dashcamd`)

## Camera System
__Note:__ Camera streaming uses gstreamer. Unfamiliar with gstreamer? There's a handy gstreamer crash course [here](http://processors.wiki.ti.com/index.php/Example_GStreamer_Pipelines).

### Design
#### Implemented
The Jetson broadcasts a 802.11n WiFi access point, and the cameras connect to it.

Camera RPi (client) >> 802.11n WiFi >> Jetson TX2 (host)

The Jetson must "open" the pipeline on a port by executing a `gst-launch-1.0` command before a Raspberry Pi executes a corresponding `gst-launch-1.0` command on that port to "close" the pipeline. Video stream only starts after the pipeline has been "closed" (this terminology will be used throughout this guide).

#### Theoretical, Type 1
The cameras broadcast streams to the Jetson via peer-to-peer WiFi, leaving the Jetson free to connect to the internet via a smartphone hotspot, router, or modem.

Camera RPi >> P2P WiFi >> Jetson TX2 >> Smartphone/Router/Modem >> Internet

#### Theoretical, Type 2
The Jetson broadcasts a 802.11n WiFi access point, and the cameras connect to it. The Jetson connects to the Internet via a LTE modem connected over PCIe or a secondary WiFi adapter connected via Ethernet or USB, sharing the connection with the camera modules.

Camera RPi (client) << 802.11n WiFi >> Jetson TX2 (host) >> LTE Modem/Secondary WiFi Adapter >> Internet

__Note:__ This may address clock skew between the Raspberry Pis and the Jetson, reducing the latency of the camera streams.

### `source/data_logging/rpicameras`
Files in this folder are designed exclusively for managing Raspberry Pi Camera Modules connected to a Raspberry Pi 3 Model B flashed with RaspbianOS. Please run `make` after modifying these files and reboot the Raspberry Pi for the changes to take effect.

#### `bchelper` and `bchelper.cpp`
Helper process that runs a `gst-launch-1.0` command and closes the backup camera pipeline. Modify these properties of the backup camera stream here:
- Bitrate
- Resolution (Width & Height, independently)
- Horizontal/Vertical Flip
- Port (default 9003)
- Streaming methodology (note, changing this will require doing the same on `backup_camera_helper.cpp` and `make`ing its corresponding executable `backup_camera_helper` on the Jetson).

#### `c1helper.cpp`, `c1helper`, `c2helper.cpp`, `c2helper`
Helper processes that run a `gst-launch-1.0` command and closes the camera pipelines for the front dashcam (`c1helper`) and rear dashcam (`c2helper`). These programs are virtually identical to `bc_helper` (with the same modifiable properties), but use different ports (port 9001 for `c1helper`, port 9002 for `c2helper`).

__Note:__ Only the front dashcam is used as of 1.0 release.

#### `rpi1dcd.cpp`, `rpi1dcd`, `rpi2dcd.cpp`, `rpi2dcd`
Camera daemons that automatically run on the Raspberry Pi controlling the front camera (`rpi1dcd.cpp`) and rear camera (`rpi2dcd.cpp`) after boot into Raspbian. These programs essentially function as a Bluetooth server, accepting a connection from the Jetson and then executing commands involving the camera helpers based on the Bluetooth command received.

## AHRS
AHRS utilizes a CHR-UM6 robot orientation sensor in conjunction with its corresponding driver, implemented in C++.
