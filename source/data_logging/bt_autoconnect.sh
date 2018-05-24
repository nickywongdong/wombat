#!/bin/bash
front=""
rear=""
obd=""
pos=0

# Read each line from file and save it to variable
while IFS='' read -r line || [[ -n "$line" ]]; do
	echo "Found BT ADDR: $line"

	if [[ "$front" == "" ]]
	then
		front=$line
	elif  [[ "$rear" == "" ]]
	then
		rear=$line
	elif  [[ "$obd" == "" ]]
	then
		obd=$line
	fi
	pos+=1
done < "bluetooth_addresses"

# Debugging: double check vars
echo $front
echo $rear

# Load bluetooth module
pactl load-module module-bluetooth-discover
sleep 1s

# Connect to cameras using bluetoothctl
# Also pair and trust
bluetoothctl << EOF
pair $front
trust $front
connect $front
pair $rear
trust $rear
connect $rear
pair $obd
trust $obd
connect $obd
EOF

# Special OBDII adapter Bluetooth connection witchcraft
