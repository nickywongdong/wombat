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

/*
  A loops that conducts all of the data logging.
  Makes calls to the python adapter and then waits 100ms
  in order to achieve ~10 samples per second.
*/
void loggingLooper(string loggingDirectory) {
  string builtCommand;
  clock_t timer1;
  chdir((const char *)loggingDirectory.c_str());
  /*string sub = ".";
  Py_SetProgramName((char *)sub.c_str());

  Py_Initialize();
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages')");
  PyRun_SimpleString("import obd");
  //PyRun_SimpleString("import dld_obd_adapter");
  Py_Finalize();*/

  while(1) {
    if(axolotlFileSystem::getAvailableMemory(loggingDirectory) > 200) {
        timer1 = clock();
        builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + loggingDirectory;
        system(builtCommand.c_str());
        //setenv("PYTHONPATH",".",1);

        #ifdef DEBUG
        printf("Logged?\n");
        printf("%f\n",(clock()-timer1)/(double)CLOCKS_PER_SEC);
        printf("Sample Rate: %f\n",1/((clock()-timer1)/(double)CLOCKS_PER_SEC));
        #endif
        usleep(1500000);
    }
  }
}

void createLogfile(string loggingDirectory) {
  if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 200) {
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

    while(axolotlFileSystem::getAvailableMemory(loggingDirectory) < 200) {
      sleep(5);
    }

    chdir((const char *)loggingDirectory.c_str());
    system("touch obd_log.csv");

    #ifdef DEBUG
    printf("Logfile created after waiting.\n");
    #endif
  }
  chdir((const char *)axolotlFileSystem::getPWD().c_str());
}

int main(int argc, char *argv[]) {
  registerSigTermHandler();

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
