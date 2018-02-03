/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter for pyOBD.

   Dependencies:
   - Python 2.7
   - pip 9.0.1
*/

#include "dcomh.hpp"
#include <python2.7/Python.h>   // for interfacing with python adapter

using namespace std;

ofstream logfile;

/*
  Handles SIGTERM to ensure safe exit.
  Closes logfile.
*/
void dldSigTermHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  logfile.close();  // close the logfile to stop logging data to it
  exit(0);
}

/*
  Registers the dldSigTermHandler with SIGTERM.
*/
void registerSigTermHandler() {
  static struct sigaction dld_sa;
  memset(&dld_sa,0,sizeof(dld_sa));
  dld_sa.sa_sigaction = dldSigTermHandler;
  dld_sa.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &dld_sa, NULL);
}

/*
  A loops that conducts all of the data logging.
  Makes calls to the python adapter and then waits 100ms
  in order to achieve ~10 samples per second.
*/
void loggingLooper(string loggingDirectory) {
  string builtCommand;
  clock_t timer1;
  chdir((const char *)loggingDirectory.c_str());
  logfile.open("obd_log.csv");
  while(1) {
    if(getAvailableMemory(loggingDirectory) > 200) {
        timer1 = clock();
        Py_SetProgramName((char *)loggingDirectory.c_str());
        Py_Initialize();
        PyRun_SimpleString("import sys;");
        builtCommand = "sys.path.append('" + getHomeDir() + "/Gitdir/wombat/source/pyobds')";
        PyRun_SimpleString((const char *)builtCommand.c_str());
        PyRun_SimpleString("import dld_pyobd_adapter");
        Py_Finalize();
        printf("Logged?\n");
        printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
        printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
    }
    usleep(100);    // wait 100ms, this is for 10Hz sample rate. adjust as needed.
  }
  logfile.close();
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
