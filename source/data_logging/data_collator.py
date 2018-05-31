################################################################################
#   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
#   Copyright (C) 2018 by Team Wombat
#   Victor Li <livic@oregonstate.edu>
#   Nick Wong <wongnich@oregonstate.edu>
#   Ryan Crane <cranery@oregonstate.edu>
#
#   This file is part of Axolotl.
#
#   Axolotl is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Axolotl is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
#   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
################################################################################

## ------------------------------------
## Data Collator
## ------------------------------------
## Assembles a master data log from the obd and ahrs logs after Axolotl quits.
##

import os
import csv
import sys

logging_directory = sys.argv[1]

obd_log = open(logging_directory + "/obd_log.csv",'r');
obd_raw = obd_log.readlines()
obd_log.close()

# Read each line of obd log into array
obd_read = []
for line in obd_raw:
    obd_read.append(line.split(','))

ahrs_log = open(logging_directory + "/ahrs_log.csv",'r');
ahrs_raw = ahrs_log.readlines()
ahrs_log.close()

# Read each line of ahrs log into array
ahrs_read = []
for line in ahrs_raw:
    ahrs_read.append(line.split(','))

print obd_read[0][0]
print ahrs_read[0][0]

# If there is an AHRS entry that matches an OBD timestamp, append the AHRS data to the end of the csv line
# Only do the first seen instance of a matching AHRS timestamp row
output_array = []
index = 0
seen = False;
for i in xrange(0,len(obd_read)):
    while True:
        # print len(obd_read[i][0])
        # print len(ahrs_read[index][0])
        # print "A--" + str("".join(obd_read[i][0].split(obd_read[i][0][4]))) + "--"
        # print "B--" + str("".join(ahrs_read[index][0].split(ahrs_read[index][0][4]))) + "--"
        print str(obd_read[i][0] == ahrs_read[index][0])
        if (obd_read[i][0] == ahrs_read[index][0]):
            seen = True;
            break;
        else:
            if ((index + 1) < len(ahrs_read)):
                index += 1
            else:
                break;
    if seen:
        obd_match_line = obd_read[i]
        obd_match_line = obd_match_line[:-1]
        ahrs_match_line = ahrs_read[index][1:]
        for item in ahrs_match_line:
            obd_match_line.append(item)
        output_array.append(obd_match_line)
        seen = False

    index = 0

# Write all of the data out to a combined log
combined_log = open(logging_directory + "/master_log.csv",'w+')
for line in output_array:
    text_line = ','.join(line)
    combined_log.write(text_line)

combined_log.close()
