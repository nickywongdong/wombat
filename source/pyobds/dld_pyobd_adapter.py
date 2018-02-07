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

# python OBD (from pyOBD-pi fork)
import obd

# pyOBD
import obd_io
import obd_sensors
import serial

def obdSnapshot(obdconnection):
    command = ""
    logTime = time.time()

    # snapshot time start (grabs computer time)
    csvLine = "@" + str(time.ctime()) + ","

    # - calculated engine load
    command = (obd.commands.ENGINE_LOAD)
    csvLine += str(obdconnection.query(command).value) + ","

    # - engine speed
    command = (obd.commands.RPM)
    csvLine += str(obdconnection.query(command).value) + ","

    # - vehicle speed
    command = (obd.commands.SPEED)
    csvLine += str(obdconnection.query(command).value) + ","

    # - throttle position
    command = (obd.commands.THROTTLE_POS)
    csvLine += str(obdconnection.query(command).value) + ","

    # - relative throttle position
    command = (obd.commands.RELATIVE_THROTTLE_POS)
    csvLine += str(obdconnection.query(command).value) + ","

    # - runtime since engine start
    command = (obd.commands.RUN_TIME)
    csvLine += str(obdconnection.query(command).value) + ","

    # - fuel tank level
    command = (obd.commands.FUEL_LEVEL)
    csvLine += str(obdconnection.query(command).value) + ","

    # - coolant temp
    command = (obd.commands.COOLANT_TEMP)
    csvLine += str(obdconnection.query(command).value) + ","

    # - oil temp
    command = (obd.commands.OIL_TEMP)
    csvLine += str(obdconnection.query(command).value) + ","

    # - ambient air temp
    command = (obd.commands.AMBIANT_AIR_TEMP)
    csvLine += str(obdconnection.query(command).value) + ","

    # - absolute barometric pressure
    command = (obd.commands.BAROMETRIC_PRESSURE)
    csvLine += str(obdconnection.query(command).value) + "\n"

    csvFileHandle = open(sys.argv[2] + "obd_log.csv",'a')
    csvFileHandle.write(csvLine)
    csvFileHandle.close()

    print str(time.time()-logTime)

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
