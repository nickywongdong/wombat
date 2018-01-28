// Axolotl Dashcam Daemon
// Dependencies:
// - gstreamer

#include "dcomh.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int dcdTermSigHandler(int sig) {
  // catch termination signals by testing apparatus/Axolotl
  // term signal causes record to dump prematurely
  exit(0); // exit status 0 if successful dump
}

void recordLooper() {
  float memAvailable;
  space_info memCheck;

  while(1) {
    memCheck = space("/Volumes/SD Transfer");
    memAvailable = (float)memCheck.available/1073741824;
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
