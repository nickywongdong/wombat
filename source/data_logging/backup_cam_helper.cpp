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
#include <string>

using namespace std;

/*
  Records a chunk of video and saves to disk.
  Must be passed the bluetooth address of the respective dashcam and the TCP
  port the Jetson is receiving the stream at.
  Port 9001: front dashcam
  Port 9002: rear dashcam
  Port 9003: backup camera
*/
int main(int argc, char *argv[]) {
  int cameraPort = atoi(argv[1]);
  string runType = argv[2], loggingDirectory = argv[3], sysCmd;

  // Create command based on port passed and execute it
  // sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! autovideosink sync=false";
  sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! textoverlay text=\"Please check your surroundings before reversing.\" valignment=bottom halignment=center font-desc=\"Sans, 12\" ! autovideosink sync=false";
  system(sysCmd.c_str());

  // Loop forever to allow process kill by camera system
  while(1) {

  }
  return 0;
}
