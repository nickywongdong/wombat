/* ------------------------------------
   Axolotl Dashcam Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs camera data from dashcam and backup camera.
*/

#include "dcomh.hpp"

using namespace std;

string loggingDirectory;
bool loggingActive = true;

pid_t dchelper0_pid, dchelper1_pid;

/*
  Records a chunk of video and saves to disk.
  Must be passed the bluetooth address of the respective dashcam and the TCP
  port the Jetson is receiving the stream at.
  Port 9001: front dashcam
  Port 9002: rear dashcam
  Port 9003: backup camera
*/
void record(string bluetoothAddress, int cameraPort) {
  //printf("Recording...\n");
  //sleep(10);
  //printf("Recording complete. Saving to file.\n");
}

/*
  Constantly loops, calling record().
*/
void cameraLooper() {
  clock_t timer1;
  while(1) {
    if(loggingActive) {
      timer1 = clock();
      if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 2048) {
        record("ASDF",9001);
      }

      #ifdef DEBUG
      printf("Logged?\n");
      printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
      printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
      #endif
    }
  }
}

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

int main(int argc, char *argv[]) {
  // Ensure that a logging directory has been provided and bind it

  loggingDirectory = argv[1];

  registerToggleOffHandler();
  registerToggleOnHandler();
  cameraLooper();

  return 0;
}
