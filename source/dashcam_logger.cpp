/* ------------------------------------
   Axolotl Dashcam Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs camera data from dashcam and backup camera.
*/

#include "dcomh.hpp"

#define DEBUG

using namespace std;

string loggingDirectory;
bool loggingActive = true;

/*
  Turns logging off.
*/
void toggleOffHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = false;
}

/*
  Registers the toggle off handler with SIGUSR1.
*/
void registerToggleOffHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = toggleOffHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &dsa, NULL);
}

/*
  Turns logging on.
*/
void toggleOnHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = true;
}

/*
  Registers the toggle handler with SIGUSR2.
*/
void registerToggleOnHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = toggleOnHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR2, &dsa, NULL);
}

// record function that will record a 5-minute chunk of video from a stream over the wlan
void record() {
  printf("Recording...\n");
  sleep(10);
  printf("Recording complete. Saving to file.\n");
}

// loops the recording function
void cameraLooper() {
  clock_t timer1;
  while(1) {
    if(loggingActive) {
      timer1 = clock();
      if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 2048) {
        record();
      }

      #ifdef DEBUG
      printf("Logged?\n");
      printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
      printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
      #endif
    }
  }
}

int main(int argc, char *argv[]) {
  // Ensure that a logging directory has been provided and bind it

  loggingDirectory = argv[1];

  registerToggleOffHandler();
  registerToggleOnHandler();
  cameraLooper();

  return 0;
}
