################################################################################
#   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
#   Copyright (C) 2018 by Team Wombat
#   Victor Li <livic@oregonstate.edu>
#   Nick Wong <wongnich@oregonstate.edu>
#   Ryan Crane <cranery@oregonstate.edu>
#
#   This file is part of Axolotl.
#
#   Axolotl is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Axolotl is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
#   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
################################################################################

## ------------------------------------
## Data Logging DTC Fetcher
## ------------------------------------
## Uses python-OBD to fetch DTC data to file.
## Only executed once when commanded by the data logging daemon.
##

import sys
import datetime
import time
import os

# python OBD (from pyOBD-pi fork)
import obd

# grabs all DTCs and outputs them to file
def fetchDTC(obd_bluetooth_handle, file_path):
    dtc_error_file = open(file_path + "/dtc_errors",'w')
    dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
    dtc_error_file.write(str(obd_bluetooth_handle.query(obd.commands.GET_DTC)))
    dtc_error_file.close()

# commands the vehicle to delete all of its stored DTCs
def clearDTC(obd_bluetooth_handle):
    obd_bluetooth_handle.query(obd.commands.CLEAR_DTC)

if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    obd_bluetooth_socket = obd.OBD()
    # obd_bluetooth_socket = obd.OBD("/dev/tty.OBDII-Port")     # experimental explicit connect command

    # Get filepath from arguments, or leave the filepath as pwd if empty
    # file_path = "."
    # if(len(sys.argv) > 2):
    #     new_path = sys.argv[1].split('/')
    #     new_path = new_path[:-2]
    #     file_path = '/'.join(new_path)

    file_path = "/home/nvidia/axolotl"

    if(obd_bluetooth_socket.is_connected()):
        # Logic based on command line arguments
        if(sys.argv[1] == "fetch"):
            fetchDTC(obd_bluetooth_socket, file_path)
        elif(sys.argv[1] == "clear"):
            clearDTC(obd_bluetooth_socket)
    else:
        dtc_error_file = open(file_path + "/dtc_errors",'w+')
        dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
        dtc_error_file.write("Error: No OBD connection detected; DTC fetch failed.")
        dtc_error_file.write(" ")
        dtc_error_file.close()
        os.system('echo \"Error: could not fetch DTCs; bluetooth connection not available.\" >> ~/axolotl/debug')

    obd_bluetooth_socket.close()
