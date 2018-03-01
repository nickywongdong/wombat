sudo killall hostapd
sudo killall wpa_supplicant 

sudo cp ap/hostapd.conf /etc/hostapd/hostapd.conf
sudo cp ap/dnsmasq.conf /etc/dnsmasq.conf
sudo cp ap/sysctl.conf /etc/sysctl.conf
sudo cp ap/interfaces /etc/network/interfaces
sudo cp ap/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf

sudo nmcli radio wifi off
sudo su -c "echo 2 > sudo /sys/module/bcmdhd/parameters/op_mode"
sudo nmcli radio wifi on

sudo service NetworkManager restart
sudo hostapd -B /etc/hostapd/hostapd.conf
