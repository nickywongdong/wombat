import os
import sys

config_file.open("/home/nvidia/.config/gqrx/default.conf",'r')
file_lines = config_file.readlines()
file_lines = file_lines[3:]
config_file.close()

config_file.open("/home/nvidia/.config/gqrx/default.conf",'w')
for line in file_lines:
    config_file.write(line)
config_file.close()
