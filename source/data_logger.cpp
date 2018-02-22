/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter.
*/

#include "dcomh.hpp"
#include <python2.7/Python.h>

#define DEBUG
#define OBD_ADAPTER_PATH "/Gitdir/wombat/source/data_obd_adapter.py"

using namespace std;

string loggingDirectory;
bool loggingActive = true;

void createLogfile();

/*
  Toggles logging off.
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
  Toggles logging on.
*/
void toggleOnHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = true;
  createLogfile();
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

/*
  A loops that conducts all of the data logging.
  Makes calls to the python adapter and then waits 100ms
  in order to achieve ~10 samples per second.
*/
void loggingLooper() {
  string builtCommand;
  clock_t timer1;
  while(1) {
    timer1 = clock();
    if (loggingActive) {
      if(axolotlFileSystem::getAvailableMemory(loggingDirectory) > 200) {
        string builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + loggingDirectory;
        system(builtCommand.c_str());
      }

      #ifdef DEBUG
      printf("Logged?\n");
      printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
      printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
      #endif
    }
    usleep(1000);
  }
}

void createLogfile() {
  string createCommand;
  if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 200) {
    createCommand = "touch " + loggingDirectory + "/obd_log.csv";
    system(createCommand.c_str());

    #ifdef DEBUG
    printf("We done got enough memory.\n");
    printf("Logfile created.\n");
    #endif
  }
  else {
    #ifdef DEBUG
    printf("Not enough free space. Waiting...");
    #endif

    while(axolotlFileSystem::getAvailableMemory(loggingDirectory) < 200) {
      sleep(5);
    }

    createCommand = "touch " + loggingDirectory + "/obd_log.csv";
    system(createCommand.c_str());

    #ifdef DEBUG
    printf("Logfile created after waiting.\n");
    #endif
  }
}

int main(int argc, char *argv[]) {

  // Ensure that a logging directory has been provided and bind it
  if (argc != 2) {
    exit(1);
  }
  loggingDirectory = argv[1];

  // Register signal handlers
  registerToggleOffHandler();
  registerToggleOnHandler();

  // Create the .csv where data will be logged
  createLogfile();

  // Start Data Logging
  loggingLooper();

  return 0;
}
