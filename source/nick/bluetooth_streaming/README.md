Following commands on https://blog.stevenocchipinti.com/2012/10/bluetooth-audio-streaming-from-phone-to.html/
	- Replaced d-feet with bluetoothctl
	- Ran bluetoothctl:
		○ Scan on
		○ Pair (phone)
		○ connectionfailed - ran pactl load-module module-bluetooth-discover
		○ Edited file /etc/pulse/daemon.conf to include the line: "resample-method = trivial" after resample… line
		○ Bluetooth remove device (phone), pair(phone)
	- Tegra now appears as speaker option for iphone
	- Testing with MacBook pair sucessful
