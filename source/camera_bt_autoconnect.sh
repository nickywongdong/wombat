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
	# bt-device --disconnect=$line
	# bt-device --connect=$line
done < "bluetooth_addresses"

echo $front
echo $rear

pactl load-module module-bluetooth-discover

bluetoothctl << EOF
connect $front
connect $rear
EOF
#sudo hidd --connect $0 > /dev/null 2>&1
#sudo hidd --connect $1 > /dev/null 2>&1
