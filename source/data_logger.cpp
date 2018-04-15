/* ------------------------------------
   Axolotl Data Logging Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs all OBDII data with the help of a Python adapter.
*/

#include "dcomh.hpp"
#include <python2.7/Python.h>

#define DEBUG
#define DATA_HELPER_ARG0 "./datad_pyhelper"

#ifdef __linux__
#define OBD_ADAPTER_PATH "/wombat/source/data_obd_logger.py"
#else
#define OBD_ADAPTER_PATH "/Gitdir/wombat/source/data_obd_logger.py"
#endif

using namespace std;

string logging_directory;
bool logging_active = true;
pid_t obd_logger_pid = -5, ahrs_logger_pid = -5;

/*
  Starts OBD and AHRS logging processes.
  Used on program start and signalled logging restarts.
*/
void startOBDLogger() {
  string built_command, curr_pid;
  int s;
  char *args[] = {(char *)DATA_HELPER_ARG0, (char *)logging_directory.c_str(), NULL};
  obd_logger_pid = fork();
  if (obd_logger_pid == 0) {
    execv("datad_pyhelper",args);   // comment out if AHRS breaks; serial port access violation
  }
  else {
    ahrs_logger_pid = fork();
    if(ahrs_logger_pid == 0) {
        char *args2[] = {(char *)DATA_HELPER_ARG0, (char *)logging_directory.c_str(), NULL};
        execv("um6/imu",args2);
    }
    else {

    }
  }
}

/*
  Main program loop.
*/
void loggingLooper() {
  startOBDLogger();
  while(1) {
    usleep(1000);
  }
}

/*
  Creates .csv files for logging.

  BUG FIX: no longer creates obd_log.csv, as imu will check for the existence of this file
  as an indicator of successful connection to thd OBDLink MX. This prevents serial port
  violations as the OBD autoconnect will no longer try to access the serial port while
  the imu program is reading from it.
*/

void createLogfiles() {
  string create_command;
  while(axolotlFileSystem::getAvailableMemory(logging_directory) < 200) {
    #ifdef DEBUG
    printf("Not enough free space. Waiting...");
    #endif
  }

  //create_command = "touch " + logging_directory + "/obd_log.csv";
  //system(create_command.c_str());

  create_command = "touch " + logging_directory + "/ahrs_log.csv";
  system(create_command.c_str());
}

/*
  Toggles logging off.
*/
void toggleOffHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  int status = 0;

  // Kills OBD process
  if(!(obd_logger_pid < 0)) {
    kill(obd_logger_pid, SIGTERM);
  }
  waitpid(obd_logger_pid, &status, 0);

  // Kills AHRS process
  if(!(ahrs_logger_pid < 0)) {
    kill(ahrs_logger_pid, SIGTERM);
  }
  waitpid(ahrs_logger_pid, &status, 0);

  // Resets globals
  logging_active = false;
  obd_logger_pid = -5;
  ahrs_logger_pid = -5;
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
  logging_active = true;
  createLogfiles();
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

  // Code verbatim from toggle off handler, save for exit(0)
  int status = 0;
  if(!(obd_logger_pid < 0)) {
    kill(obd_logger_pid, SIGKILL);
  }
  waitpid(obd_logger_pid, &status, 0);

  if(!(ahrs_logger_pid < 0)) {
    kill(ahrs_logger_pid, SIGKILL);
  }
  waitpid(ahrs_logger_pid, &status, 0);
  logging_active = false;
  obd_logger_pid = -5;
  ahrs_logger_pid = -5;

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

/*
  Calls the fuel economy analysis script and the DTC fetch script.
*/
void updateDataFiles(int signumber, siginfo_t *siginfo, void *pointer) {
  string python_command = "python fuel_economy_analysis.py " + logging_directory;
  system(python_command.c_str());
  python_command = "python data_obd_dtc.py fetchDTC " + logging_directory;
  system(python_command.c_str());
}

/*
  Registers the fuel economy analysis update handler with SIGBUS.
*/
void registerUpdateHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = updateDataFiles;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGBUS, &dsa, NULL);
}

int main(int argc, char *argv[]) {

  // Ensure that a logging directory has been provided and save it to a variable
  if (argc != 2) {
    exit(1);
  }
  logging_directory = argv[1];

  // Register signal handlers
  registerToggleOffHandler();
  registerToggleOnHandler();
  registerSigtermHandler();
  registerUpdateHandler();

  // Prepare the .csvs
  createLogfiles();

  // Starts the main progrma loop
  loggingLooper();

  return 0;
}
