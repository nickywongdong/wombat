## ------------------------------------
## Axolotl Data Logging Python Adapter
## ------------------------------------
## Describes methods that interact with pyOBD's IO interface
## to gather and log data on behalf of the data logging daemon.
##
## Dependencies:
## - pyOBD
## - pySerial 3.4
## - wxPython 4.0.0b2

import sys

import obd_io
import obd_sensors
import serial
import datetime
import time

def obdSnapshot():
    print "Snapshotted OBDII status to file."

def fetchDTC():
    print "Fetched DTC codes to file."

def clearDTC():
    print "Cleared DTC codes!"

if __name__ == '__main__':
    if(sys.argv[1] == "snapshot"):
        obdSnapshot()
    elif(sys.argv[1] == "fetch"):
        fetchDTC()
    elif(sys.argv[1] == "clear"):
        clearDTC()
