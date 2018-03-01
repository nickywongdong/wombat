sudo killall hostapd
sudo killall wpa_supplicant

sudo cp orig/bcmdhd.conf /etc/modprobe.d/bcmdhd.conf
sudo cp orig/hostapd.conf /etc/hostapd/hostapd.conf
sudo cp orig/sysctl.conf /etc/sysctl.conf
sudo cp orig/interfaces /etc/network/interfaces
sudo cp orig/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf

sudo service NetworkManager restart
sudo service wpa_supplicant start
