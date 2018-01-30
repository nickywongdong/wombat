// Axolotl Dashcam Daemon
// Dependencies:
// - gstreamer

#include "dcomh.hpp"

using namespace std;

int dcdTermSigHandler(int sig) {
  // catch termination signals by testing apparatus/Axolotl
  // term signal causes record to dump prematurely
  exit(0); // exit status 0 if successful dump
}

// This is where video recording happens.
void record() {
  printf("Recording...\n");
  sleep(10);
  printf("Recording complete. Saving to file.\n");
}

void recordLooper() {
  while(1) {
    if (getAvailableMemory("/Volumes/SD Transfer") > 2048) {
      record();
    }
    else {
      printf("Not enough free space. Waiting...");
      // Write error to debug.txt log for the day!
      sleep(5);
    }
  }
}

int main(int argc, char *argv[]) {
    printf("Logging Directory: %s\n",argv[argc-1]);
    recordLooper();
    return 0;
}
