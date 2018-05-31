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
