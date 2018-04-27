#!/bin/bash
while [ True ] ;
 do echo -ne $(cat /sys/class/gpio/gpio186/value) "\r";
  sleep 0.1;
  done