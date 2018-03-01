sudo killall hostapd
sudo killall wpa_supplicant

sudo cp ap/bcmdhd.conf /etc/modprobe.d/bcmdhd.conf
sudo cp ap/hostapd.conf /etc/hostapd/hostapd.conf
sudo cp ap/sysctl.conf /etc/sysctl.conf
sudo cp ap/interfaces /etc/network/interfaces
sudo cp ap/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf

sudo service NetworKManager restart
sudo service wpa_supplicant start
