import time
import sys
import os
import csv
import string

samples = 0
stopsamples = 0
accelsamples = 0

totalspeed = 0.0

show_stopstart_tip = False
show_averagespeed_tip = False
show_acceleration_tip = False

speed_low = False

# Grabbing the CSV data and organizing it
with open('test_obd_log.csv', 'r') as csvfile:
    fereader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in fereader:
        samples += 1

        speedarr = row[3].split(' ')
        if(speedarr[0] != "None"):
            totalspeed += float(speedarr[0])
            if(speedarr[0] == "0"):
                stopsamples += 1

        throttlearr = row[4].split(' ')
        if(throttlearr[0] != "None"):
            if(float(throttlearr[0]) > 60):
                accelsamples += 1

# Doing some checks
if (totalspeed/samples < 40) or (totalspeed/samples > 105):
    show_averagespeed_tip = True
    if (totalspeed/samples < 60):
        speed_low = True

if (float(stopsamples)/float(samples) > 0.4):
    show_stopstart_tip = True

if (float(accelsamples)/float(samples) > 0.4):
    show_acceleration_tip = True

print show_stopstart_tip
print show_acceleration_tip
print show_averagespeed_tip

print "Please obey all speed laws when considering these instructions."

if show_stopstart_tip or show_acceleration_tip or show_averagespeed_tip:
    if show_averagespeed_tip:
        if speed_low:
            print "Avoid driving too slowly; slow speeds means your vehicle cannot use higher gearing and results in worse fuel economy."
        else:
            print "Avoid driving too fast; reduced speed reduces drag and increased fuel economy."
else:
    print "No tips to report!"
