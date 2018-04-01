import time
import sys
import os
import csv
import string

samples = 0
stopsamples = 0

totalspeed = 0.0

show_stopstart_tip = False
show_averagespeed_tip = False
show_acceleration_tip = False

with open('test_obd_log.csv', 'r') as csvfile:
    fereader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in fereader:
        samples += 1
        speedarr = row[3].split(' ')
        if(speedarr[0] != "None"):
            totalspeed += float(speedarr[0])
        if(speedarr[0] == "0 kph"):
            stopsamples += 1

print "Average Speed: " + str(totalspeed/float(samples))
