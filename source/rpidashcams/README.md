# rpidashcams

Files in this directory are not used on the Jetson.

Instead, each RaspberryPi 3 and Camera Module V2 pair needs to have this source code saved to the `~/wombat/source directory`; `make` then needs to be called with this directory as the PWD on the RaspberryPi.

Currently working on:
- Rewriting a rc.local file for each RaspberryPi to connect to its parent Jetson via Bluetooth automatically and execute its corresponding daemon
- Rewriting wpasupplicant.conf to automatically connect to the Jetson's AP WiFi

## Notes:
Each RaspberryPi should be connected to a USB power source that provides at least 5V and 1.2A. A 12V car adapter supplying 2.4A of current is recommended at minimum.
