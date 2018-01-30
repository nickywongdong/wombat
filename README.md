# Axolotl - Victor's Branch
__Current Version:__ 0.1.7 pre-alpha

Version Changes:
- Implemented dynamic directory creation, so the system creates one directory per start-up instance.
- Modified execv to pass the directory information to the dashcam daemon so it knows where to save data to.

Dependencies:
- Navit PACKAGE_VERSION 0.5.1\*
- pyOBD PACKAGE_VERSION 0.9.3
- boost PACKAGE_VERSION 1.66.0 (Unix)
- Python 2.7.3

\*Navit dependencies not included in this listing. 
