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

/* ------------------------------------
   Dashcam Record Helper
   ------------------------------------
   Helper process that opens the pipeline for the RaspberryPis.
   Seems redundant, but encapsulating this within its own program allows for logging stop/restart.
*/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>

using namespace std;

/*
  Opens a video pipeline at a given port so that we can receive a RPi stream on that port.
*/
int main(int argc, char *argv[]) {

  int camera_port = atoi(argv[1]);
  string run_type = argv[2], logging_directory = argv[3], stream_open_command;

  if(run_type == "f") {
    stream_open_command = "gst-launch-1.0 -e -v udpsrc port=" + to_string(camera_port) + " ! application/x-rtp, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! h264parse ! splitmuxsink max-size-time=300000000000 location='" + logging_directory + "/front_dashcam%03d.mp4'";
  }
  else if (run_type == "r") {
    stream_open_command = "gst-launch-1.0 -e -v udpsrc port=" + to_string(camera_port) + " ! application/x-rtp, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! h264parse ! splitmuxsink max-size-time=300000000000 location='" + logging_directory + "/rear_dashcam%03d.mp4'";
  }

  system(stream_open_command.c_str());
  while(1) {

  }
  return 0;
}
