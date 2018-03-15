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
  /*if(argc != 3) {
    exit(0);
  }*/

  int cameraPort = atoi(argv[1]);
  string runType = argv[2], loggingDirectory = argv[3], sysCmd;

  if(runType == "r") {
    sysCmd = "gst-launch-1.0 -e -v udpsrc port=" + to_string(cameraPort) + " ! application/x-rtp, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! h264parse ! mp4mux ! splitmuxsink location='" + loggingDirectory + "/front_dashcam%03d.mp4'";
  }
  else if (runType == "w") {
    sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! autovideosink sync=false";
  }

  system(sysCmd.c_str());
  while(1) {

  }
  return 0;
}
