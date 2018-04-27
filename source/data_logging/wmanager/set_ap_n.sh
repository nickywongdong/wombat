sudo killall hostapd
sudo killall wpa_supplicant

sleep 1

sudo cp ap_n/bcmdhd.conf /etc/modprobe.d/bcmdhd.conf
sudo cp ap_n/hostapd.conf /etc/hostapd/hostapd.conf
sudo cp ap_n/dnsmasq.conf /etc/dnsmasq.conf
sudo cp ap_n/sysctl.conf /etc/sysctl.conf
sudo cp ap_n/interfaces /etc/network/interfaces
sudo cp ap_n/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf

rfkill unblock all

sudo nmcli radio wifi off
sudo su -c "echo 2 > /sys/module/bcmdhd/parameters/op_mode"
sudo nmcli radio wifi on

sudo service NetworkManager restart

sudo ifconfig wlan0 192.168.8.1 netmask 255.255.255.0 up

sudo service dnsmasq start
sudo hostapd -B /etc/hostapd/hostapd.conf
