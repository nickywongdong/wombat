#H1 rpidashcams

Files in this directory are not used on the Jetson. 

Instead, each RaspberryPi 3 and Camera Module V2 pair needs to have this source code saved to the `~/wombat/source directory`; `make` then needs to be called whilst within this directory.

Currently working on:
- Rewriting a rc.local file for each RaspberryPi to connect to its parent Jetson via Bluetooth automatically and execute its corresponding daemon
- Rewriting wpasupplicant.conf to automatically connect to the Jetson's AP WiFi
