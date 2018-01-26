// Axolotl Dashcam Daemon
// Dependencies:
// - gstreamer

#include "dcomh.h"

using namespace std;

int dcdTermSigHandler(int sig) {
  // catch termination signals by testing apparatus/Axolotl
  // term signal causes record to dump prematurely
  exit(0); // exit status 0 if successful dump
}

void recordLooper() {
  double memAvailable;
  while(1) {
    // do memory check, store in memAvailable
    memAvailable =
    if (memAvailable > 2.0) {
      continue;
    }
    else {
      sleep(5);
      continue;
    }
  }
}

int record() {
  // record at 1080p30 for 300s
  return 0;
}

int main() {
    while(1) {
      sleep(1);
      printf("Hi?\n");
    }
    return 0;
}
