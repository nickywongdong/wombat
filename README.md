# Axolotl - Victor's Branch
__Current Version:__ 0.2.1 pre-alpha

Version 0.2.1:
- Fully working data logging, with a few bugs
- Switched to python-OBD library for all OBD functions, so removed pyOBD source and updated dependency list

Version 0.1.11:
- Initial implementation of python OBD adapter
- Changed dependencies, using python-OBD for OBDII data
- Removed data logging daemon's signal handlers as C++ program no longer handles the OBDII data
- Added extra field to OBDII data: oil temp

Version 0.1.10:
- Added SHA256 hashing function to complete implementation of password check for black box data deletion
- Completed integration of python script into data logging daemon
- Added new tests to testing apparatus
- Initialized pyOBD as a module
- Added salted SHA256 hash of default data deletion key

Version 0.1.9:
- Changed navigation GUI to simplified mobile version supplied by Navit devs
- Switched GUI rendering engine from GTK to Qt for later integration

Version 0.1.8:
- Added signal handler to data logging daemon
- Added code comments
- Partial implementation of data deletion function
- Fixed bug with directory creation where singular minutes would be recorded as only one digit
- Added get user home directory function to common header file

Dependencies:
- Navit 0.5.1\*
- boost 1.66.0 (Unix)
- Python 2.7.3
- Qt 5.10\*
- CryptoPP 6.0.0
- python-OBD 0.6.1

\*Sub-dependencies not included in this listing.
