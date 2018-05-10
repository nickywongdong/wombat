import sys
import time

for i in xrange(0,8):
    csv_line = "@" + str(time.ctime()) + ",1,2,3,4\n"
    csv_file_handle = open("obd_log.csv",'a')
    csv_file_handle.write(csv_line)
    csv_file_handle.close()
    time.sleep(1)
