sudo killall hostapd
sudo killall wpa_supplicant

sudo cp orig/sysctl.conf /etc/sysctl.conf
sudo cp orig/interfaces /etc/network/interfaces
sudo cp orig/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf

sudo nmcli radio wifi off
sudo su -c "echo 0 > /sys/module/bcmdhd/parameters/op_mode"
sudo nmcli radio wifi on

sudo service NetworkManager restart
sudo service wpa_supplicant start
