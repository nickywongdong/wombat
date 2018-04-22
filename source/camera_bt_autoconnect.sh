#! /bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
	echo "Found BT ADDR: $line"
	bt-device --disconnect=$line
	bt-device --connect=$line
done < "bluetooth_addresses"

echo $0
echo $1

#sudo hidd --connect $0 > /dev/null 2>&1
#sudo hidd --connect $1 > /dev/null 2>&1
