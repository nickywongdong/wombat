#!/usr/bin/expect

#this script will allow a bluetooth device to be connected to the Jetson TX2 Tegra Ubuntu
#will have to be run on every reboot, or bluetooth restart.

#for this to work, the system needs to have the following installed:
#pulseaudio
#bluetoothctl


### TESTING  COMMAND LINE:
#echo "First arg: $1"


#make sure the following files have the following lies of code in it:

#file: /etc/pulse/daemon.conf include the line: "resample-method = trivial" after the other resample-method line
#file: /etc/bluetooth/main.conf   "Enable=Gateway,Source,Socket"


#attempt to restart bluetooth service, not sure how bash will ask for sudo privileges
#sudo service bluetooth restart

#load module for bluetooth connection, may still fail after loading this module however

#spawn pactl

#send "unload-module module-bluetooth-discover\r"
#send "load-module module-bluetooth-discover\r"
#sleep 1
#puts "loading bluetooth dscover module\r"
#sleep 1
#send "load-module module-loopback\r"
#sleep 1
#puts "loading module loopback"
#connect to the bluetooth device, can attempt this as many times as you need, or else show failure. Must fill in the bluetooth address here.
##catch output of bluetoothctl connect in a variable, to see if it failed or not

#catch=$( { bluetoothctl connect $1; } 2>&1 )


##keep trying if we have a failure, make sure to update string in statement to the actual output of bluetoothctl
#until [ $catch -ne "failed" ]
#do
#	echo $catch
#	catch=$( { bluetoothctl connect $1; } 2>&1 )
#done

##testing output:
#echo $catch


#pacmd list-sources
#pacmd list-sinks

#hard code the bluetooth address for now

set ADDRESS "70:70:0D:87:4D:D4"
#bluez_source xxxx =  is the bluetooth mac address, output = speaker
#set xxxx to the speaker source
#send "connecting to: " $ADDRESS

spawn bluetoothctl
send "connect $ADDRESS\r"
sleep 4
#puts "connected\r"
send "quit\r"
sleep 1

spawn /home/nvidia/Desktop/github/source/bluetooth_streaming/load_module.sh

#spawn pacmd
#send "load-module module-loopback source=bluez_source.$ADDRESS sink=alsa_output.platform-3510000.hda.hdmi-stereo-extra1\r"

#spawn pactl
#send "load-module module-loopback\r"
#sleep 1
#puts "loading module loopback\r"
#sleep 1

expect eof