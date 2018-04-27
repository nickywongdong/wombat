#!/bin/bash


bluetoothctl << EOF
power on
discoverable on
pairable on
exit
exit
EOF

bluetoothctl | grep -o "[[:xdigit:]:]\{11,17\}"

pacmd load-module module-loopback source=bluez_source.70_70_0D_87_4D_D4 sink=alsa_output.platform-3510000.hda.hdmi-stereo-extra1

