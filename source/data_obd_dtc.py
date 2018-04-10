## ------------------------------------
## Axolotl Data Logging DTC Fetcher
## ------------------------------------
## Describes methods that interact with python-OBD's to fetch DTC data to file.
## Script is only executed once when commanded by the data logger process.
##

import sys
import datetime
import time

# python OBD (from pyOBD-pi fork)
import obd

# grabs all DTCs and outputs them to file
def fetchDTC(obd_bluetooth_handle, file_path):
    dtc_error_file = open(file_path + "/dtc_errors",'a')
    dtc_error_file.write(str(obd_bluetooth_handle.query(obd.commands.GET_DTC)))
    dtc_error_file.close()

# commands the vehicle to delete all of its stored DTCs
def clearDTC(obd_bluetooth_handle):
    obd_bluetooth_handle.query(obd.commands.CLEAR_DTC)

if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    obd_bluetooth_socket = obd.OBD()
    # obd_bluetooth_socket = obd.OBD("/dev/tty.OBDII-Port")

    path = "."
    if (len(sys.argv) > 2):
        path = sys.argv[2]

    if(sys.argv[1] == "fetch"):
        fetchDTC(obd_bluetooth_socket, file_path)
    elif(sys.argv[1] == "clear"):
        clearDTC(obd_bluetooth_socket)

    obd_bluetooth_socket.close()
