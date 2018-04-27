## ------------------------------------
## Axolotl Data Logging DTC Fetcher
## ------------------------------------
## Describes methods that interact with python-OBD's to fetch DTC data to file.
## Script is only executed once when commanded by the data logger process.
##

import sys
import datetime
import time
import os

# python OBD (from pyOBD-pi fork)
import obd

# grabs all DTCs and outputs them to file
def fetchDTC(obd_bluetooth_handle, file_path):
    try:
        dtc_error_file = open(file_path + "/dtcs",'w')
        dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
        dtc_error_file.write(str(obd_bluetooth_handle.query(obd.commands.GET_DTC)))
        dtc_error_file.close()
    except IOError:
        os.system('echo \"Error: failed to open log dtcs file to write DTCs.\" >> ~/axolotl/debug')

    try:
        dtc_error_file = open("/home/nvidia/axolotl/dtcs",'w')
        dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
        dtc_error_file.write(str(obd_bluetooth_handle.query(obd.commands.GET_DTC)))
        dtc_error_file.close()
    except IOError:
        os.system('echo \"Error: failed to open system dtcs file to write DTCs.\" >> ~/axolotl/debug')

# commands the vehicle to delete all of its stored DTCs
def clearDTC(obd_bluetooth_handle):
    obd_bluetooth_handle.query(obd.commands.CLEAR_DTC)

if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    obd_bluetooth_socket = obd.OBD()
    # obd_bluetooth_socket = obd.OBD("/dev/tty.OBDII-Port")     # experimental explicit connect command

    # Get filepath from arguments, or leave the filepath as pwd if empty
    file_path = "."
    if(len(sys.argv) > 2):
        new_path = sys.argv[1]

    if(obd_bluetooth_socket.is_connected()):
        # Logic based on command line arguments
        if(sys.argv[2] == "fetch"):
            fetchDTC(obd_bluetooth_socket, file_path)
        elif(sys.argv[2] == "clear"):
            clearDTC(obd_bluetooth_socket)
    else:
        try:
            dtc_error_file = open(file_path + "/dtcs",'w+')
            dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
            dtc_error_file.write("Error: No OBD connection detected; DTC fetch failed.")
            dtc_error_file.write(" ")
            dtc_error_file.close()
        except IOError:
            os.system('echo \"Error: failed to open log dtcs file to write DTCs.\" >> ~/axolotl/debug')

        try:
            dtc_error_file = open("/home/nvidia/axolotl/dtcs",'w+')
            dtc_error_file.write("Diagnostic Trouble Codes fetched at: " + time.ctime() + "\n\n")
            dtc_error_file.write("Error: No OBD connection detected; DTC fetch failed.")
            dtc_error_file.write(" ")
            dtc_error_file.close()
        except IOError:
            os.system('echo \"Error: failed to open system dtcs file to write DTCs.\" >> ~/axolotl/debug')

        os.system('echo \"Error: could not fetch DTCs; bluetooth connection not available.\" >> ~/axolotl/debug')

    obd_bluetooth_socket.close()
