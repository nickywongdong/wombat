## ------------------------------------
## Axolotl Data Logging Python Adapter
## ------------------------------------
## Describes methods that interact with pyOBD's IO interface to gather and log data on behalf of the data logging helper.
## This script will automatically quit if the parent datad_pyhelper process is killed.
##
## Dependencies:
## - python-OBD
## - Python 2.7

import os
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
commands.append(obd.commands.AMBIANT_AIR_TEMP)
commands.append(obd.commands.BAROMETRIC_PRESSURE)

# diagnostic commands for development
diagCommands = []

diagCommands.append(obd.commands.HYBRID_BATTERY_REMAINING)
diagCommands.append(obd.commands.OIL_TEMP)


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

    ########################################
    # same operations for diagnostics...
    csvLine = "@" + str(time.ctime()) + ","

    # execute the command array, saving results to csvLine with "," delimitation
    for i in xrange(0,len(diagCommands)-1):
            csvLine += str(obdConnection.query(diagCommands[i]).value) + ","

    csvLine += str(obdConnection.query(diagCommands[len(diagCommands)-1]).value) + "\n"

    # write entire csvLine to file in one file operation
    csvFileHandle = open(sys.argv[2] + "/diag.csv",'a')
    csvFileHandle.write(csvLine)
    csvFileHandle.close()
    ########################################

    # debug statement; outputs the time taken to complete the query
    print str(time.time()-logTime)

# set the command array to watch mode, allowing for async non-blocking updates
def obdAsync(obdConnection):
    for i in xrange(0, len(commands)-1):
        obdConnection.watch(commands[i])

# starts watching on the OBD connection
def startAsyncWatch(obdConnection):
    for i in xrange(0,len(commands)-1):
        obdConnection.watch(commands[i])

    # diagnostic commands
    for i in xrange(0,len(diagCommands)-1):
        obdConnection.watch(diagCommands[i])
        obdConnection.supported_commands.add(diagCommands[i])

    obdConnection.start()


if __name__ == '__main__':
    ## Set up connection to the OBDLink MX
    if runAsync:
        obdBluetoothConnection = obd.Async()
        startAsyncWatch(obdBluetoothConnection)
    else:
        obdBluetoothConnection = obd.OBD()

    ## Logic based on command line call
    if(sys.argv[1] == "snapshot"):
        while(1):
            try:
                os.kill(int(sys.argv[3]),0);
            except OSError:
                break;
            else:
                obdSnapshot(obdBluetoothConnection)
                time.sleep(.2)

    obdBluetoothConnection.close()
