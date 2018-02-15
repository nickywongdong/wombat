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

# establish a global command array
commands = []

# setting up the command array
commands.append(obd.commands.ENGINE_LOAD)
commands.append(obd.commands.RPM)
commands.append(obd.commands.SPEED)
commands.append(obd.commands.THROTTLE_POS)
commands.append(obd.commands.RELATIVE_THROTTLE_POS)
commands.append(obd.commands.RUN_TIME)
commands.append(obd.commands.FUEL_LEVEL)
commands.append(obd.commands.COOLANT_TEMP)
commands.append(obd.commands.OIL_TEMP)
commands.append(obd.commands.AMBIANT_AIR_TEMP)
commands.append(obd.commands.BAROMETRIC_PRESSURE)

# run in async mode?
runAsync = True

def obdSnapshot(obdConnection):
    logTime = time.time()

    # snapshot time start (grabs computer time)
    csvLine = "@" + str(time.ctime()) + ","

    # execute the command array, saving results to csvLine with "," delimitation
    for i in xrange(0,len(commands)-1):
            csvLine += str(obdConnection.query(commands[i]).value) + ","

    csvLine += str(obdConnection.query(commands[len(commands)-1]).value) + "\n"

    # write entire csvLine to file in one file operation
    csvFileHandle = open(sys.argv[2] + "/obd_log.csv",'a')
    csvFileHandle.write(csvLine)
    csvFileHandle.close()

    # debug statement; outputs the time taken to complete the query
    print str(time.time()-logTime)

# grabs all DTCs and outputs them to file
def fetchDTC(obdConnection):
    dtcErrorFile = open(sys.argv[2] + "/dtcErrors",'a')
    dtcErrorFile.write(str(obdConnection.query(obd.commands.GET_DTC)))
    dtcErrorFile.close()
    print "Fetched DTC codes to file."

# commands the vehicle to delete all of its stored DTCs
def clearDTC(obdConnection):
    obdConnection.query(obd.commands.CLEAR_DTC)
    print "Cleared DTC codes!"

# set the command array to watch mode, allowing for async non-blocking updates
def obdAsync(obdConnection):
    for i in xrange(0, len(commands)):
        obdConnection.watch(commands[i])

if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    if runAsync:
        obdBluetoothConnection = obd.Async(baudrate=115200,fast=True)
    else:
        obdBluetoothConnection = obd.OBD(baudrate=115200,fast=True)

    ## Logic based on command line call
    if(sys.argv[1] == "snapshot"):
        obdSnapshot(obdBluetoothConnection)
    elif(sys.argv[1] == "fetch"):
        fetchDTC(obdBluetoothConnection)
    elif(sys.argv[1] == "clear"):
        clearDTC(obdBluetoothConnection)

    obdBluetoothConnection.close()
