// Axolotl Dashcam Daemon
// Dependencies:
// - videosoftware


#include "dcomh.h"

int dcdTermSigHandler(int sig) {
  // catch termination signals by testing apparatus/Axolotl
  // term signal causes record to dump prematurely
  exit(0); // exit status 0 if successful dump
}

void recordLooper() {
  double memAvailable;
  while(1) {
    // do memory check, store in memAvailable
    if (memAvailable > 2.0) {

    }
    else {
      wait(5);
      continue;
    }
  }
}

int record() {

}

int main() {

    return 0;
}
