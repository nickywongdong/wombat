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
  sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! autovideosink sync=false";
  system(sysCmd.c_str());

  // Loop forever to allow process kill by camera system
  while(1) {

  }
  return 0;
}
