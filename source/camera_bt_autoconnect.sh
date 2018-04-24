#!/bin/bash
front=""
rear=""
pos=0

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

echo $front
echo $rear

pactl load-module module-bluetooth-discover

bluetoothctl << EOF
connect $front
connect $rear
exit
EOF
