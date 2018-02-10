/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter.
*/

#include "dcomh.hpp"
#include <python2.7/Python.h>

#define DEBUG
#define OBD_ADAPTER_PATH "/Gitdir/wombat/source/dld_obd_adapter.py"

using namespace std;

string loggingDirectory;

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

    if(axolotlFileSystem::getAvailableMemory(loggingDirectory) > 200) {
      string builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + loggingDirectory;
      system(builtCommand.c_str());
    }
    usleep(100);

    #ifdef DEBUG
    printf("Logged?\n");
    printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
    printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
    #endif
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
  if (argc != 1) {
    exit(1);
  }
  loggingDirectory = argv[0];

  // Create the .csv where data will be logged
  createLogfile();

  // Start Data Logging
  loggingLooper();

  return 0;
}
