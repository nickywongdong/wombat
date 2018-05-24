## ------------------------------------
## GQRX Configuration Remover
## ------------------------------------
## Modifies the GQRX config file so we always get a successful boot.
##

import os
import sys
import time

config_file = open("/home/nvidia/.config/gqrx/default.conf",'r')
file_lines = config_file.readlines()
config_file.close()

# file_lines = file_lines[3:]

config_file = open("/home/nvidia/.config/gqrx/default.conf",'w')
for line in file_lines:
    if not ("crash" in line):
        config_file.write(line)
config_file.close()
