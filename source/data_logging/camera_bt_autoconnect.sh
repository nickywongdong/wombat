#!/bin/bash
front=""
rear=""
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
	fi
	pos+=1
done < "bluetooth_addresses"

# Debugging: double check vars
echo $front
echo $rear

# Load bluetooth module
pactl load-module module-bluetooth-discover

# Connect to cameras using bluetoothctl
bluetoothctl << EOF
connect $front
connect $rear
EOF
