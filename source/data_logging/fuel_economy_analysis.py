## ------------------------------------
## Axolotl Fuel Economy Analysis Script
## ------------------------------------
##
## A script called by the data logging daemon after being signaled by
## the daemon manager. Makes a duplicate of the current obd_log and then
## runs some fuel economy analysis on the data.
##

import time
import sys
import os
import csv
import string
from subprocess import call
# from pathlib import Path

# Variables to hold fuel economy data and output status
samples = 0
stopsamples = 0
accelsamples = 0

totalspeed = 0.0
speed_low = False

show_stopstart_tip = False
show_averagespeed_tip = False
show_acceleration_tip = False

# Variables that hold path and filename
path = "."
filename = 'test_obd_log.csv'

# Grab path data from arguments
if (len(sys.argv) > 1):
    path = sys.argv[1]
    os.chdir(path)      # change path to logging directory
    call(["cp","obd_log.csv","test_obd_log.csv"])   # duplicate the csv

if os.access(filename, os.W_OK):
    # Read the data from the csv and do some analysis
    with open(filename, 'r') as csvfile:
        fereader = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in fereader:
            # Counts number of samples
            samples += 1

            # For average speed
            speedarr = row[3].split(' ')
            if(speedarr[0] != "None"):
                totalspeed += float(speedarr[0])
                if(speedarr[0] == "0"):
                    stopsamples += 1

            # For throttle position above 60%
            throttlearr = row[4].split(' ')
            if(throttlearr[0] != "None"):
                if(float(throttlearr[0]) > 60):
                    accelsamples += 1

    # Doing some checks
    if not samples == 0:
        if (totalspeed/samples < 40) or (totalspeed/samples > 105):
            show_averagespeed_tip = True
            if (totalspeed/samples < 60):
                speed_low = True

        if (float(stopsamples)/float(samples) > 0.4):
            show_stopstart_tip = True

        if (float(accelsamples)/float(samples) > 0.4):
            show_acceleration_tip = True

    # Print status of bools for tips
    print show_stopstart_tip
    print show_acceleration_tip
    print show_averagespeed_tip

    # Master copy for system display
    try:
        tipsOutputFile = open("/home/nvidia/axolotl/fedata",'w+')
        tipsOutputFile.write("Fuel Economy Analysis completed at: " + time.ctime() + "\n\n")
        tipsOutputFile.write("Please obey all speed laws when considering these instructions.\n\n")

        if show_stopstart_tip or show_acceleration_tip or show_averagespeed_tip:
            tipsOutputFile.write("Recommendations:\n");
            if show_averagespeed_tip:
                if speed_low:
                    tipsOutputFile.write("- Avoid driving too slowly; slow speeds means your vehicle cannot use higher gearing and results in worse fuel economy.\n")
                else:
                    tipsOutputFile.write("- Avoid driving too fast; reduced speed reduces drag and increased fuel economy.\n")
            if show_acceleration_tip:
                tipsOutputFile.write("- Gently ease onto the accelerator; aggressive acceleration wastes fuel.\n")
            if show_stopstart_tip:
                tipsOutputFile.write("- Try to minimize your idling; idling wastes fuel.\n")
        else:
            tipsOutputFile.write("No tips to report!\n")

        tipsOutputFile.close()
    except IOError:
        os.system('echo \"Error: could not open file to write fuel economy analysis.\" >> ~/axolotl/debug')


    # Data log copy for this boot cycle
    try:
        tipsOutputFile = open("fedata",'w+')
        tipsOutputFile.write("Fuel Economy Analysis completed at: " + time.ctime() + "\n\n")
        tipsOutputFile.write("Please obey all speed laws when considering these instructions.\n\n")

        if show_stopstart_tip or show_acceleration_tip or show_averagespeed_tip:
            tipsOutputFile.write("Recommendations:\n");
            if show_averagespeed_tip:
                if speed_low:
                    tipsOutputFile.write("- Avoid driving too slowly; slow speeds means your vehicle cannot use higher gearing and results in worse fuel economy.\n")
                else:
                    tipsOutputFile.write("- Avoid driving too fast; reduced speed reduces drag and increased fuel economy.\n")
            if show_acceleration_tip:
                tipsOutputFile.write("- Gently ease onto the accelerator; aggressive acceleration wastes fuel.\n")
            if show_stopstart_tip:
                tipsOutputFile.write("- Try to minimize your idling; idling wastes fuel.\n")
        else:
            tipsOutputFile.write("No tips to report!\n")

        tipsOutputFile.close()
    except IOError:
        os.system('echo \"Error: could not open file to write fuel economy analysis.\" >> ~/axolotl/debug')

else:
    # Master copy for system display
    try:
        tipsOutputFile = open("/home/nvidia/axolotl/fedata",'w+')
        tipsOutputFile.write("Fuel Economy Analysis completed at: " + time.ctime() + "\n\n")
        tipsOutputFile.write("Error: no OBD log detected for analysis. Please check your OBD connection.")
        tipsOutputFile.close()
    except IOError:
        os.system('echo \"Error: could not open file to write fuel economy analysis.\" >> ~/axolotl/debug')

    # Data log copy for this boot cycle
    try:
        tipsOutputFile = open("fedata",'w+')
        tipsOutputFile.write("Fuel Economy Analysis completed at: " + time.ctime() + "\n\n")
        tipsOutputFile.write("Error: no OBD log detected for analysis. Please check your OBD connection.")
        tipsOutputFile.close()
    except IOError:
        os.system('echo \"Error: could not open file to write fuel economy analysis.\" >> ~/axolotl/debug')

    os.system('echo \"Error: could not analyze fuel data due to missing OBD log.\" >> ~/axolotl/debug')
