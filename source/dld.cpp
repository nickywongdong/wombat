/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter for pyOBD.
*/

#include "dcomh.hpp"

using namespace std;

ofstream logfile;

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
        printf("Logged?\n");
        printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
        printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
    }
    sleep(1);
  }
}

void createLogfile(string loggingDirectory) {
  if (getAvailableMemory(loggingDirectory) > 200) {
    printf("We done got enough memory.\n");
    chdir((const char *)loggingDirectory.c_str());
    system("touch obd_log.csv");
    printf("Logfile created.\n");
  }
  else {
    printf("Not enough free space. Waiting...");
    while(getAvailableMemory(loggingDirectory) < 200) {
      sleep(5);
    }
    chdir((const char *)loggingDirectory.c_str());
    system("touch obd_log.csv");
    printf("Logfile created after waiting.\n");
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
  printf("OBDII logging ready!");

  // Start Data Logging
  loggingLooper(loggingDirectory);

  return 0;
}
