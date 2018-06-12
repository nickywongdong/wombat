/*******************************************************************************
*   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
*   Copyright (C) 2018 by Team Wombat
*   Victor Li <livic@oregonstate.edu>
*   Nick Wong <wongnich@oregonstate.edu>
*   Ryan Crane <cranery@oregonstate.edu>
*
*   This file is part of Axolotl.
*
*   Axolotl is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   Axolotl is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
*   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
  sleep(3);
  system("raspivid -t 0 -w 1920 -h 1080 -fps 30 -g 5 -b 1000000 -vf -o - | gst-launch-1.0 --gst-debug=3 fdsrc ! h264parse ! video/x-h264, format=byte-stream ! rtph264pay ! udpsink host=192.168.8.1 port=9001");
  return 0;
}
