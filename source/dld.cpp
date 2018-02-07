/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter for pyOBD.
*/

#include "dcomh.hpp"

#define DEBUG

using namespace std;

/*
  A loops that conducts all of the data logging.
  Makes calls to the python adapter and then waits 100ms
  in order to achieve ~10 samples per second.
*/
void loggingLooper(string loggingDirectory) {
  string builtCommand;
  clock_t timer1;
  chdir((const char *)loggingDirectory.c_str());
  while(1) {
    if(getAvailableMemory(loggingDirectory) > 200) {
        timer1 = clock();
        builtCommand = "python " + getHomeDir() + "/Gitdir/wombat/source/pyobds/dld_pyobd_adapter.py snapshot " + loggingDirectory;
        system(builtCommand.c_str());

        #ifdef DEBUG
        printf("Logged?\n");
        printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
        printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
        #endif
    }
    sleep(1);
  }
}

void createLogfile(string loggingDirectory) {
  if (getAvailableMemory(loggingDirectory) > 200) {
    chdir((const char *)loggingDirectory.c_str());
    system("touch obd_log.csv");

    #ifdef DEBUG
    printf("We done got enough memory.\n");
    printf("Logfile created.\n");
    #endif
  }
  else {
    #ifdef DEBUG
    printf("Not enough free space. Waiting...");
    #endif

    while(getAvailableMemory(loggingDirectory) < 200) {
      sleep(5);
    }

    chdir((const char *)loggingDirectory.c_str());
    system("touch obd_log.csv");

    #ifdef DEBUG
    printf("Logfile created after waiting.\n");
    #endif
  }
  chdir((const char *)getPWD().c_str());
}

int main(int argc, char *argv[]) {
  
  // Ensure that a logging directory has been provided and bind it
  string loggingDirectory;
  if (argc != 1) {
    exit(1);
  }
  loggingDirectory = argv[0];

  // Create the .csv where data will be logged
  createLogfile(loggingDirectory);

  // Start Data Logging
  loggingLooper(loggingDirectory);

  return 0;
}
