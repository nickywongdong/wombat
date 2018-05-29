# Developer Guide
This contains documentation regarding developing for Axolotl.

## Connectivity
Axolotl uses the Jetson's WiFi antennas to broadcast an 802.11n AP network at 2.4GHz; AP WiFi mode is __required__ for camera functionality. WiFi is managed by two scripts in the `source/data_logging/wmanager` directory: set_ap_n.sh and set_client.sh.

__set_ap_n.sh__ puts the Jetson in AP WiFi host mode, __set_client.sh__ puts the Jetson in default client mode. Only use __set_client.sh__ if wireless internet connection is desired for development/debugging. Otherwise, return the Jetson to host mode with __set_ap_n.sh__.

It may be easier to use a wired Ethernet connection and/or USB to SSH into the Jetson TX2 Development Kit for development.


## Camera System Design

### Implemented
Camera RPi (client)    <--- 802.11n WiFi --->    Jetson TX2 (host)

### Theoretical, Type 1
Camera RPi    <--- P2P WiFi --->    Jetson TX2    <--- 2.4GHz or 5.0GHz Access Point (Smartphone/Router/Modem) --->    Internet

### Theoretical, Type 2
Camera RPi (client)    <--- 802.11n WiFi --->    Jetson TX2 (host)    <--- LTE modem --->   Internet
