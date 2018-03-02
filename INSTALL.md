# Installing Navigation and Data logging

1.  Run the install script with sudo privileges: `sudo ./installdep.sh`. The Jetson will now reboot.
2.  In the `/acm` directory, and run: `sudo ./installCDCACM.sh`.
3.  Download the maps binary at the link provided in README.md (or just click on the link when viewing this branch on Github).
4.  Move the maps binary to the `~/axolotl/maps` folder (create any directories that don't exist).
5.  In the `source` directory, run `make`.
6.  Done!
    - Data logging system can be run by executing `./daemon_launcher` in `source`.
    - Navigation system can be run by executing `./navit` in `navit_build/navit/`.
