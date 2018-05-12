import os
import sys
import csv

obd_log = open("../test_files/test_obd_log.csv",'r');
obd_raw = obd_log.readlines()
obd_log.close()

# Read each line of obd log into array
obd_read = []
for line in obd_raw:
    obd_read.append(line.split(','))

tot = 0
for i in obd_read:
    tot = tot + len(i)

if ((tot / len(obd_read)) >= 11):
    print "DATA_INTEGRITY_TEST: OBD LOG INTEGRITY CHECKS OUT"
else:
    print "DATA_INTEGRITY_TEST: OBD LOG INTEGRITY FAILURE"

ahrs_log = open("../test_files/test_obd_log.csv",'r');
ahrs_raw = ahrs_log.readlines()
ahrs_log.close()

# Read each line of obd log into array
ahrs_read = []
for line in ahrs_raw:
    ahrs_read.append(line.split(','))

tot = 0
for i in ahrs_read:
    tot = tot + len(i)

if ((tot / len(obd_read)) >= 4):
    print "DATA_INTEGRITY_TEST: AHRS LOG INTEGRITY CHECKS OUT"
else:
    print "DATA_INTEGRITY_TEST: AHRS LOG INTEGRITY FAILURE"
