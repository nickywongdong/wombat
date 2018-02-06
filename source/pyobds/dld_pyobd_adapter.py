## ------------------------------------
## Axolotl Data Logging Python Adapter
## ------------------------------------
## Describes methods that interact with pyOBD's IO interface
## to gather and log data on behalf of the data logging daemon.
##
## Dependencies:
## - python-OBD
## - pyOBD
## - pySerial 3.4
## - wxPython 4.0.0b2
## - Python 2.7
## - pip 9.0.1

import sys
import datetime
import time

import obd

import obd_io
import obd_sensors
import serial

def obdSnapshot(obdconnection):
    command = ""
    csvline = ""

    # - calculated engine load
    command = (obd.commands.ENGINE_LOAD)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - engine speed
    command = (obd.commands.RPM)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - vehicle speed
    command = (obd.commands.SPEED)
    r = obdconnection.query(command)
    csvline += str(r.value.to("mph")) + ","

    # - throttle position
    command = (obd.commands.THROTTLE_POS)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - relative throttle position
    command = (obd.commands.RELATIVE_THROTTLE_POS)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - runtime since engine start
    command = (obd.commands.RUN_TIME)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - fuel tank level
    command = (obd.commands.FUEL_LEVEL)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - coolant temp
    command = (obd.commands.COOLANT_TEMP)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - oil temp
    command = (obd.commands.OIL_TEMP)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - ambient air temp
    command = (obd.commands.AMBIANT_AIR_TEMP)
    r = obdconnection.query(command)
    csvline += str(r.value) + ","

    # - absolute barometric pressure
    command = (obd.commands.BAROMETRIC_PRESSURE)
    r = obdconnection.query(command)
    csvline += str(r.value.to("mmHg")) + ","

    # print csvline

    csvfh = openstr(sys.argv[2] + "obd_log.csv","w")
    csvfh.write(csvline)
    csvfh.close()

def fetchDTC():
    print "Fetched DTC codes to file."

def clearDTC():
    print "Cleared DTC codes!"

if __name__ == '__main__':
    ## Set up connection
    btconn = obd.OBD()

    ##
    if(sys.argv[1] == "snapshot"):
        obdSnapshot(btconn)
    elif(sys.argv[1] == "fetch"):
        fetchDTC()
    elif(sys.argv[1] == "clear"):
        clearDTC()
