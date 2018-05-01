/* ------------------------------------
   Axolotl Daemon Manager
   ------------------------------------
   Process that sets up the environment for data logging and starts
   all processes that execute data logging.
*/

#include "dcomh.hpp"
#include <sys/stat.h>

// DEPRECATED: system-specific save volume selection
// uncomment if an external storage device is connected
// external storage device MUST be named "AXOLOTLDCV"
// Jetson MUST be logged into the "nvidia" profile
//#define LOG_VOLUME_INSTALLED
// #if defined(__linux__) && defined(LOG_VOLUME_INSTALLED)
// #define LOG_VOLUME "/media/nvidia/AXOLOTLDCV"
// #else
// #define LOG_VOLUME axolotlFileSystem::getHomeDir()
// #endif

#define DCDARG1 "./dashcamd"
#define DLDARG1 "./datad"
#define PST -8

#define DEBUG
#define LOGTEST

using namespace std;

pid_t dcdpid = -5, dldpid = -5;

string logging_directory, run_directory, log_volume, auto_delete;

/*
  Checks the supplied password against the stored password.
*/
bool checkPasswordCorrect(string password) {
  string truekey;
  ifstream truekeyf;
  string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey"; //normally run_directory + "/hashkey"
  truekeyf.open(hash_file_path);
  if(truekeyf.is_open()) {
    getline(truekeyf,truekey);
  }
  truekeyf.close();
  return (axolotlFileSystem::hash(password) == truekey);
}

/*
  Creates a logging directory from a path.
*/
bool buildSaveDirectoryFromPath(string path) {
  string base_directory_str = log_volume, data_dir_create_command = "mkdir -p " + base_directory_str + "/axolotl/data";
  system(data_dir_create_command.c_str());
  bool dir_build_status;
  do {
    dir_build_status = mkdir((const char *)path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    sleep(1);
  }
  while (dir_build_status == false);
  return dir_build_status;
}

/*
  Builds the save directory for both daemons.
  Returns the path to the directory that was created.
  /axolotl/data must exist in the user's home directory or this won't work.

  From here to final: instead of axolotlFileSystem::getHomeDir(), hardcode the mounted volume.
*/
bool buildSaveDirectory() {
  // Getting info to build data storage directory
  int dir_build_status = 2;
  string dirPrefix = "/axolotl/data/axolotl_log_", base_directory_str = log_volume, create_directory_name = base_directory_str + dirPrefix;

  // create the base axolotl data directory if it doesn't exist
  string data_dir_create_command = "mkdir -p " + base_directory_str + "/axolotl/data";
  system(data_dir_create_command.c_str());

  // Fetch and proces datetime data
  time_t raw_time = time(NULL);
  struct tm *processed_time = localtime(&raw_time);
  string year_str = to_string(processed_time->tm_year+1900);
  string month_str = to_string(processed_time->tm_mon+1);
  string day_str = to_string(processed_time->tm_mday);

  int processed_seconds = processed_time->tm_sec;
  string seconds_str = to_string(processed_seconds);
  if(processed_seconds < 10) {
    seconds_str = "0" + seconds_str;    // ensures that seconds are always 2 digits
  }

  int processed_minutes = processed_time->tm_min;
  string minutes_str = to_string(processed_minutes);
  if(processed_minutes < 10) {
    minutes_str = "0" + minutes_str;    // ensures that minutes are always 2 digits
  }

  int processed_hours = processed_time->tm_hour;
  string hour_str = "" + to_string(processed_hours);
  if(processed_hours < 10) {
    hour_str = "0" + hour_str;    // ensures that hours are always 2 digits
  }

  // Assemble path
  create_directory_name = create_directory_name + year_str + "_" + month_str + "_" + day_str + "_" + hour_str + minutes_str + seconds_str;

  // Build the directory from path
  dir_build_status = mkdir((const char *)create_directory_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

  // Set global logging logging_directory
  logging_directory = create_directory_name;

  // Return success or failure
  if(dir_build_status != 0) {
    return false;
  }
  return true;
}

/*
  Handles all data deletion.
*/
void dataDeletionHandler() {
  int status = 0;

  // #define DELETION_METHOD_1
  #ifdef DELETION_METHOD_1
  // pause both daemons
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGUSR1);
  }
  if(!(dldpid < 0)) {
    kill(dldpid,SIGUSR1);
  }

  sleep(2);

  // delete the data directory
  string base_directory_str = log_volume, delete_dir = base_directory_str + "/axolotl/data", deleteCommand = "rm -rf " + delete_dir;
  system(deleteCommand.c_str());

  // rebuild the data directory using existing path so as to not break our daemons
  bool dir_build_status = buildSaveDirectoryFromPath(logging_directory);
  while(dir_build_status == false) {
    sleep(1);
    dir_build_status = buildSaveDirectoryFromPath(logging_directory);
  }
  #endif

  #ifndef DELETION_METHOD_1
  // new data deletion method
  // deletes everything but the currently active logging directory
  string current_dir = getcwd();
  string base_dir = log_volume + "/axolotl/data";
  string delete_command = "rm -rf !(" + logging_directory + ")";

  chdir(base_dir.c_str());
  system("shopt -s extglob");
  system(delete_command.c_str());
  #endif

  #ifdef DELETION_METHOD_1
  // restart both daemons
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGUSR2);
  }
  if(!(dldpid < 0)) {
    kill(dldpid,SIGUSR2);
  }
  #endif
}

/*
  Wipes all data from the data logging system.
  Will only destroy data if password matches.
*/
void deleteData(string password) {
  // Get true passkey hash from file
  ifstream hash_file;
  string truekeyHash = NULL;
  string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey"; //normally run_directory + "/hashkey"
  hash_file.open(hash_file_path);
  if (hash_file.is_open()) {
    getline(hash_file,truekeyHash);
    hash_file.close();
  }

  // Delete the data only if password hashes match
  if(axolotlFileSystem::hash(password) == truekeyHash) {
    dataDeletionHandler();
  }
  #ifdef DEBUG
  printf("Data deleted.\n");
  #endif
}

/*
  Hashes a new password and changes old password hash with the new hash.
  Only if old password matches!
*/
bool changePassword(string checkPassword, string newPassword) {
  if(checkPasswordCorrect(checkPassword)) {
    ofstream hash_file;
    string newhash = axolotlFileSystem::hash(newPassword);
    string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey";    // normally run_directory + "/hashkey"
    hash_file.open(hash_file_path, std::ofstream::trunc);
    if(hash_file.is_open()) {
      hash_file.write((const char *)newhash.c_str(),(long)newhash.length());
    }
    hash_file.close();
    return true;
  }
  return false;
}

/*
  Resets password back to the original.
*/
void resetPassword() {
  ofstream hash_file;
  string newhash = axolotlFileSystem::hash("orangemonkeyeagle");
  string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey"; // normally run_directory + "/hashkey"
  hash_file.open(hash_file_path, std::ofstream::trunc);
  if(hash_file.is_open()) {
    hash_file.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hash_file.close();
}

/*
  Handles exit of daemon launcher; kills daemons and frees their resources.
  UI: signal SIGINT to this process on system exit.
*/

void managerSigintHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  int status = 0;

  // kill and wait on termination of dashcam daemon
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGTERM);
  }
  waitpid(dcdpid, &status, 0);

  // kill and wait on termination of data logging daemon
  if(!(dldpid < 0)) {
    kill(dldpid,SIGTERM);
  }
  waitpid(dldpid, &status, 0);

  #ifdef RESET_WIFI
  chdir("wmanager");
  system("./set_client.sh");
  #endif

  // exit cleanly
  exit(0);
}

/*
  Registers the signal handler with SIGINT.
*/
void registerSigintHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = managerSigintHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGINT, &dsa, NULL);
}

/*
  Handles SIGUSR1 and initiates data deletion.
  FOR DEBUG ONLY: remove this and its signal registerer for final build.
*/

void managerDeleteHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  dataDeletionHandler();
}

/*
  Registers the delete handler with SIGUSR1.
  FOR TESTING ONLY: remove this function on final build.
*/
void registerDeleteHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = managerDeleteHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &dsa, NULL);
}

/*
  Pauses data logging, signals the data logger to update files for DTCs
  as well as fuel ecomnomy data, and restarts data logging.
*/
void updateDataHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  if(dldpid > 1) {
    kill(dldpid,SIGBUS);
  }
  sleep(5);
}

/*
  Registers the update handler with SIGUSR2.
*/
void registerUpdateHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = updateDataHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGBUS, &dsa, NULL);
}

//int mainOperation() {
int main() {
  string input_str;
  run_directory = axolotlFileSystem::getPWD();

  // Clear this boot cycle's debug file
  system("rm -f ~/axolotl/debug");
  system("rm -f ~/axolotl/device_free");

  // Test for connected flash drive
  struct stat buffer;
  auto_delete = "0";
  if ((stat("/media/nvidia/AXOLOTLDCV", &buffer) == 0) && S_ISDIR(buffer.st_mode)) {
    log_volume = "/media/nvidia/AXOLOTLDCV";
  }
  else {
    log_volume = axolotlFileSystem::getHomeDir();
    system("echo \"Warning: could not find an external 'AXOLOTLDCV'. Logging to internal storage.\" >> ~/axolotl/debug");
    auto_delete = "1";
  }

  // Registering signal handlers
  registerSigintHandler();
  registerDeleteHandler();
  registerUpdateHandler();

  // Build logging directory
  bool dir_status = buildSaveDirectory();
  while(dir_status == false) {
    sleep(1);
    dir_status = buildSaveDirectory();
  }

  char *args[] = {(char *)DLDARG1, (char *)logging_directory.c_str(), NULL};

  // Fork OBD/AHRS logger and dashcam logger
  dldpid = fork();
  if (dldpid == 0){
    #ifdef DEBUG
    printf("Trying to exec datad...\n");
    #endif
    execv("datad", args);
  }
  else {
    #ifdef DEBUG
    printf(" ");
    #endif
    char *args2[] = {(char *)DCDARG1, (char *)logging_directory.c_str(), (char *)auto_delete.c_str(), NULL};

    // forking dashcam daemon
    dcdpid = fork();
    if (dcdpid == 0){
      #ifdef DEBUG
      printf("Trying to exec dashcamd...\n");
      #endif
      execv("dashcamd", args2);
    }
    else {
      #ifdef DEBUG
      printf(" ");
      #endif
      while(1) {

      }
    }
  }

  // manager waits on quit
  while(1) {
    getline(cin,input_str);
    if(checkPasswordCorrect(input_str)) {
      dataDeletionHandler();
    }
    input_str = "";
  }

  return 0;
}
