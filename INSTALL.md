# Installing Navigation and Data logging

1.  Run the install script with sudo privileges: `sudo ./installdep.sh`
    The Jetson will now reboot.
2.  In the `/acm` directory, run: `sudo ./installCDCACM.sh`
3.  Open the README.md in this directory and download the maps binary at the link provided.
4.  Move the maps binary to the `~/axolotl/maps` folder (create directories if they don't exist).
5.  Navigate to the `source` directory and run `make`.
6.  Done!
    - Data logging system can be run by executing `./daemon_launcher`.
    - Navigation system can be run by executing `./navit` in `navit_build/navit/`.
    
