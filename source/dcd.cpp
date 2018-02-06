/* ------------------------------------
   Axolotl Dashcam Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs camera data from dashcam and backup camera.

   Dependencies:
   - Gstreamer
*/

#include "dcomh.hpp"

using namespace std;

void dcdSigTermHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  exit(0);
}

/*
  Registers the dldSigTermHandler with SIGTERM.
*/
void registerSigTermHandler() {
  static struct sigaction dcd_sa;
  memset(&dcd_sa, 0, sizeof(dcd_sa));
  dcd_sa.sa_sigaction = dcdSigTermHandler;
  dcd_sa.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &dcd_sa, NULL);
}


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
    printf("Logging Directory: %i %s\n",argc-1,argv[argc-1]);
    recordLooper();
    return 0;
}
