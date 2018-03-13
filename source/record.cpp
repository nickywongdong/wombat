#include <iostream>
#include <cstdlib>
#include <unistd.h>

/*
  Records a chunk of video and saves to disk.
  Must be passed the bluetooth address of the respective dashcam and the TCP
  port the Jetson is receiving the stream at.
  Port 9001: front dashcam
  Port 9002: rear dashcam
  Port 9003: backup camera
*/
int main(int argc; char *argv[]) {
  //printf("Recording...\n");
  //sleep(10);
  //printf("Recording complete. Saving to file.\n");
  int cameraPort = atoi(argv[1]);
  sendBluetoothCommand(s,'s');

  string sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! autovideosink sync=false";

  system(sysCmd.c_str());
  while(1) {

  }
  return 0;
}
