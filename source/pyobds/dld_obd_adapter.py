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
    logTime = time.time()

    # snapshot time start (grabs computer time)
    csvLine = "@" + str(time.ctime()) + ","

    # - calculated engine load
    csvLine += str(obdconnection.query(obd.commands.ENGINE_LOAD).value) + ","

    # - engine speed
    csvLine += str(obdconnection.query(obd.commands.RPM).value) + ","

    # - vehicle speed
    csvLine += str(obdconnection.query(obd.commands.SPEED).value) + ","

    # - throttle position
    csvLine += str(obdconnection.query(obd.commands.THROTTLE_POS).value) + ","

    # - relative throttle position
    csvLine += str(obdconnection.query(obd.commands.RELATIVE_THROTTLE_POS).value) + ","

    # - runtime since engine start
    csvLine += str(obdconnection.query(obd.commands.RUN_TIME).value) + ","

    # - fuel tank level
    csvLine += str(obdconnection.query(obd.commands.FUEL_LEVEL).value) + ","

    # - coolant temp
    csvLine += str(obdconnection.query(obd.commands.COOLANT_TEMP).value) + ","

    # - oil temp
    csvLine += str(obdconnection.query(obd.commands.OIL_TEMP).value) + ","

    # - ambient air temp
    csvLine += str(obdconnection.query(obd.commands.AMBIANT_AIR_TEMP).value) + ","

    # - absolute barometric pressure
    csvLine += str(obdconnection.query(obd.commands.BAROMETRIC_PRESSURE).value) + "\n"

    # write entire line to file in one file operation
    csvFileHandle = open(sys.argv[2] + "obd_log.csv",'a')
    csvFileHandle.write(csvLine)
    csvFileHandle.close()

    print str(time.time()-logTime)

def fetchDTC(obdconnection):
    dtcResult = obdconnection.query(obd.commands.GET_DTC)
    dtcErrorFile = open("dtcErrors.csv","a")
    dtcErrorFile.close()
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
