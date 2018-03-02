/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter.
*/

#include "dcomh.hpp"
#include <python2.7/Python.h>

#define DEBUG
#define OBD_ADAPTER_PATH "/wombat/source/data_obd_logger.py"
#define DATAHELPERARG0 "./datad_pyhelper"

using namespace std;

string loggingDirectory;
bool loggingActive = true;
pid_t obdLoggerPid = -5;

/*
  Spawns the process managing OBD logging.
*/
void startOBDLogger() {
  string builtCommand, currPid;
  int s;
  char *args[] = {(char *)DATAHELPERARG0, (char *)loggingDirectory.c_str(), NULL};
  obdLoggerPid = fork();
  if (obdLoggerPid == -1) {
    printf("Failed to spawn logging process...\n");
  }
  else if (obdLoggerPid == 0) {
    execv("datad_pyhelper",args);
  }
}

/*
  A loops that conducts all of the data logging.
*/
void loggingLooper() {
  startOBDLogger();
  while(1) {
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

/*
  Toggles logging off.
*/
void toggleOffHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  int status = 0;
  if(!(obdLoggerPid < 0)) {
    kill(obdLoggerPid, SIGTERM);
  }
  waitpid(obdLoggerPid, &status, 0);
  loggingActive = false;
  obdLoggerPid = -5;
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
  startOBDLogger();
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
  Kills the subservient logging process and ends this process safely.
*/
void datadSigtermHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  int status = 0;
  if(!(obdLoggerPid < 0)) {
    kill(obdLoggerPid, SIGKILL);
  }
  waitpid(obdLoggerPid, &status, 0);
  loggingActive = false;
  obdLoggerPid = -5;
  exit(0);
}

/*
  Registers the toggle off handler with SIGTERM.
*/
void registerSigtermHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = datadSigtermHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &dsa, NULL);
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
  registerSigtermHandler();

  // Create the .csv where data will be logged
  createLogfile();

  // Start Data Logging
  loggingLooper();

  return 0;
}
