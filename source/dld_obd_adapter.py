## ------------------------------------
## Axolotl Data Logging Python Adapter
## ------------------------------------
## Describes methods that interact with pyOBD's IO interface
## to gather and log data on behalf of the data logging daemon.
##
## Dependencies:
## - python-OBD
## - pyOBD
##      - pySerial 3.4
##      - wxPython 4.0.0b2
##      - pip 9.0.1
## - Python 2.7

import sys
import datetime
import time

# python OBD (from pyOBD-pi fork)
import obd

# pyOBD
from pyobds import obd_io
from pyobds import obd_sensors
import serial

def obdSnapshot(obdConnection):
    logTime = time.time()

    # snapshot time start (grabs computer time)
    csvLine = "@" + str(time.ctime()) + ","

    # - calculated engine load
    csvLine += str(obdConnection.query(obd.commands.ENGINE_LOAD).value) + ","

    # - engine speed
    csvLine += str(obdConnection.query(obd.commands.RPM).value) + ","

    # - vehicle speed
    csvLine += str(obdConnection.query(obd.commands.SPEED).value) + ","

    # - throttle position
    csvLine += str(obdConnection.query(obd.commands.THROTTLE_POS).value) + ","

    # - relative throttle position
    csvLine += str(obdConnection.query(obd.commands.RELATIVE_THROTTLE_POS).value) + ","

    # - runtime since engine start
    csvLine += str(obdConnection.query(obd.commands.RUN_TIME).value) + ","

    # - fuel tank level
    csvLine += str(obdConnection.query(obd.commands.FUEL_LEVEL).value) + ","

    # - coolant temp
    csvLine += str(obdConnection.query(obd.commands.COOLANT_TEMP).value) + ","

    # - oil temp
    csvLine += str(obdConnection.query(obd.commands.OIL_TEMP).value) + ","

    # - ambient air temp
    csvLine += str(obdConnection.query(obd.commands.AMBIANT_AIR_TEMP).value) + ","

    # - absolute barometric pressure
    csvLine += str(obdConnection.query(obd.commands.BAROMETRIC_PRESSURE).value) + "\n"

    # write entire line to file in one file operation
    csvFileHandle = open(sys.argv[2] + "/obd_log.csv",'a')
    csvFileHandle.write(csvLine)
    csvFileHandle.close()

    print str(time.time()-logTime)

def fetchDTC(obdConnection):
    dtcErrorFile = open(sys.argv[2] + "/dtcErrors",'a')
    dtcErrorFile.write(str(obdConnection.query(obd.commands.GET_DTC)))
    dtcErrorFile.close()
    print "Fetched DTC codes to file."

def clearDTC(obdConnection):
    obdConnection.query(obd.commands.CLEAR_DTC)
    print "Cleared DTC codes!"

if __name__ == '__main__':
    ## Set up connection
    obdBluetoothConnection = obd.OBD()

    ## Logic
    if(sys.argv[1] == "snapshot"):
        obdSnapshot(obdBluetoothConnection)
    elif(sys.argv[1] == "fetch"):
        fetchDTC(obdBluetoothConnection)
    elif(sys.argv[1] == "clear"):
        clearDTC(obdBluetoothConnection)
