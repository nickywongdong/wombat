# Data Log Formatting

## obd_log.csv

From left to right:

| **Field** | **Units** |
| --------- | --------- |
| Timestamp | Date/Time (24hr) |
| Engine Load | Percent |
| Engine Speed | RPM |
| Vehicle Speed | KPH |
| Throttle Position | Percent |
| Relative Throttle Position | Percent |
| Runtime Since Engine Start | Seconds |
| Fuel Level | Percent |
| Coolant Temp | Celsius |
| Ambient Air Temp | Celsius |
| Barometric Pressure | Kilopascal |

## ahrs_log.csv

From left to right:

| **Field** | **Units** |
| --------- | --------- |
| Pitch | Degrees |
| Roll | Degrees |
| Yaw | Degrees |

Note that AHRS orientation is based on the PCB facing right-side up and the serial port end facing towards you.
