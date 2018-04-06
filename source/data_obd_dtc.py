## ------------------------------------
## Axolotl Data Logging Python Adapter
## ------------------------------------
## Describes methods that interact with pyOBD's IO interface
## to gather and log data on behalf of the data logging daemon.
##
## Dependencies:
## - python-OBD
## - Python 2.7

import sys
import datetime
import time

# python OBD (from pyOBD-pi fork)
import obd

# grabs all DTCs and outputs them to file
def fetchDTC(obd_bluetooth_handle):
    dtc_error_file = open(sys.argv[2] + "/dtc_errors",'a')
    dtc_error_file.write(str(obd_bluetooth_handle.query(obd.commands.GET_DTC)))
    dtc_error_file.close()

# commands the vehicle to delete all of its stored DTCs
def clearDTC(obd_bluetooth_handle):
    obd_bluetooth_handle.query(obd.commands.CLEAR_DTC)

# set the command array to watch mode, allowing for async non-blocking updates
def obdAsync(obd_bluetooth_handle):
    for i in xrange(0, len(commands)):
        obd_bluetooth_handle.watch(commands[i])

# get the file path to the dtc log
def getDTCFilePath():
    return sys.argv[2] + "/dtc_errors"


if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    obd_bluetooth_socket = obd.OBD()

    if(sys.argv[1] == "fetch"):
        fetchDTC(obd_bluetooth_socket)
    elif(sys.argv[1] == "clear"):
        clearDTC(obd_bluetooth_socket)

    obd_bluetooth_socket.close()
