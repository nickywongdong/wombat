/* ------------------------------------
   Axolotl Daemon Manager
   ------------------------------------
   Process that sets up the environment for data logging and starts
   all processes that execute data logging.
*/

#include "dcomh.hpp"

// uncomment if an external storage device is connected
// external storage device MUST be named "AXOLOTLDCV"
// Jetson MUST be logged into the "nvidia" profile
//#define LOG_VOLUME_INSTALLED

#if defined(__linux__) && defined(LOG_VOLUME_INSTALLED)
#define LOG_VOLUME "/media/nvidia/AXOLOTLDCV"
#else
#define LOG_VOLUME axolotlFileSystem::getHomeDir()
#endif

#define DCDARG1 "./dashcamd"
#define DLDARG1 "./datad"
#define PST -8

#define DEBUG
#define LOGTEST

using namespace std;

pid_t dcdpid = -5, dldpid = -5;

string loggingDirectory, runDirectory;

/*
  Checks the supplied password against the stored password.
*/
bool checkPasswordCorrect(string password) {
  string truekey;
  ifstream truekeyf;
  string hashfilePath = "~/wombat/source/hashkey"; //normally runDirectory + "/hashkey"
  truekeyf.open(hashfilePath);
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
  string dirBase = LOG_VOLUME, createDataDir = "mkdir -p " + dirBase + "/axolotl/data";
  system(createDataDir.c_str());
  bool buildStatus;
  do {
    buildStatus = mkdir((const char *)path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    sleep(1);
  }
  while (buildStatus == false);
  return buildStatus;
}

/*
  Builds the save directory for both daemons.
  Returns the path to the directory that was created.
  /axolotl/data must exist in the user's home directory or this won't work.

  From here to final: instead of axolotlFileSystem::getHomeDir(), hardcode the mounted volume.
*/
bool buildSaveDirectory() {
  // Getting info to build data storage directory
  int buildStatus = 2;
  string dirPrefix = "/axolotl/data/axolotl_log_", dirBase = LOG_VOLUME, dirName = dirBase + dirPrefix;

  // create the base axolotl data directory if it doesn't exist
  string createDataDir = "mkdir -p " + dirBase + "/axolotl/data";
  system(createDataDir.c_str());

  // Fetch and proces datetime data
  time_t startTime = time(NULL);
  struct tm *startTimeAsUTC = gmtime(&startTime);
  string startYear = to_string(startTimeAsUTC->tm_year+1900);
  string startMonth = to_string(startTimeAsUTC->tm_mon+1);
  string startDay = to_string(startTimeAsUTC->tm_mday);

  int startSecProcessed = startTimeAsUTC->tm_sec;
  string startSec = to_string(startSecProcessed);
  if(startSecProcessed < 10) {
    startSec = "0" + startSec;    // ensures that seconds are always 2 digits
  }

  int startMinProcessed = startTimeAsUTC->tm_min;
  string startMin = to_string(startMinProcessed);
  if(startMinProcessed < 10) {
    startMin = "0" + startMin;    // ensures that minutes are always 2 digits
  }

  long startHourProcessed = startTimeAsUTC->tm_hour+PST;
  if(startHourProcessed < 0) {
    startHourProcessed += 24;   // adjusts if UTC-8 is earlier than UTC midnight
    startDay = to_string(startTimeAsUTC->tm_mday-1);    // day rollback if UTC is 1 day ahead of PST
  }
  string startHour = "" + to_string(startHourProcessed);
  if(startHourProcessed < 10) {
    startHour = "0" + startHour;    // ensures that hours are always 2 digits
  }

  // Assemble path
  dirName = dirName + startYear + "_" + startMonth + "_" + startDay + "_" + startHour + startMin + startSec;

  // Build the directory from path
  buildStatus = mkdir((const char *)dirName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

  // Set global logging loggingDirectory
  loggingDirectory = dirName;

  // Return success or failure
  if(buildStatus != 0) {
    return false;
  }
  return true;
}

/*
  Handles all data deletion.
*/
void dataDeletionHandler() {
  int status = 0;

  // pause both daemons
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGUSR1);
  }
  if(!(dldpid < 0)) {
    kill(dldpid,SIGUSR1);
  }

  sleep(2);

  // delete the data directory
  string dirBase = LOG_VOLUME, deleteDir = dirBase + "/axolotl/data", deleteCommand = "rm -rf " + deleteDir;
  system(deleteCommand.c_str());

  // rebuild the data directory using existing path so as to not break our daemons
  bool buildStatus = buildSaveDirectoryFromPath(loggingDirectory);
  while(buildStatus == false) {
    sleep(1);
    buildStatus = buildSaveDirectoryFromPath(loggingDirectory);
  }

  // restart both daemons
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGUSR2);
  }
  if(!(dldpid < 0)) {
    kill(dldpid,SIGUSR2);
  }
}

/*
  Wipes all data from the data logging system.
  Will only destroy data if password matches.
*/
void deleteData(string password) {
  // Get true passkey hash from file
  ifstream hashfile;
  string truekeyHash = NULL;
  string hashfilePath = "~/wombat/source/hashkey"; //normally runDirectory + "/hashkey"
  hashfile.open(hashfilePath);
  if (hashfile.is_open()) {
    getline(hashfile,truekeyHash);
    hashfile.close();
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
    ofstream hashfile;
    string newhash = axolotlFileSystem::hash(newPassword);
    string hashfilePath = "~/wombat/source/hashkey";    // normally runDirectory + "/hashkey"
    hashfile.open(hashfilePath, std::ofstream::trunc);
    if(hashfile.is_open()) {
      hashfile.write((const char *)newhash.c_str(),(long)newhash.length());
    }
    hashfile.close();
    return true;
  }
  return false;
}

/*
  Resets password back to the original.
*/
void resetPassword() {
  ofstream hashfile;
  string newhash = axolotlFileSystem::hash("orangemonkeyeagle");
  string hashfilePath = "~/wombat/source/hashkey"; // normally runDirectory + "/hashkey"
  hashfile.open(hashfilePath, std::ofstream::trunc);
  if(hashfile.is_open()) {
    hashfile.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hashfile.close();
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

//int mainOperation() {
int main() {
  string inputStr;
  runDirectory = axolotlFileSystem::getPWD();

  // Registering signal handlers
  registerSigintHandler();
  registerDeleteHandler();

  // Testing password check and hashing
  #ifdef KEYTEST
  printf("Checking true key: %i\n",checkPasswordCorrect("orangemonkeyeagle"));
  #endif

  // Data Logging Daemon Test
  #ifdef LOGTEST
  bool dirStatus = buildSaveDirectory();
  while(dirStatus == false) {
    sleep(1);
    dirStatus = buildSaveDirectory();
  }

  char *args[] = {(char *)DLDARG1, (char *)loggingDirectory.c_str(), NULL};

  // forking data logging daemon
  dldpid = fork();
  if (dldpid == -1) {
    printf("Error spawning data logging daemon... \n");
  }
  else if (dldpid == 0){
    printf("Trying to exec datad...\n");
    execv("datad", args);
  }
  else {
    printf(" ");
    char *args2[] = {(char *)DCDARG1, (char *)loggingDirectory.c_str(), NULL};

    // forking dashcam daemon
    dcdpid = fork();
    if (dcdpid == -1) {
      printf("Error spawning dashcam daemon... \n");
    }
    else if (dcdpid == 0){
      printf("Trying to exec dashcamd...\n");
      execv("dashcamd", args2);
    }
    else {
      printf(" ");
    }
  }

  // manager waits on quit
  while(1) {
    getline(cin,inputStr);
    if(checkPasswordCorrect(inputStr)) {
      dataDeletionHandler();
    }
    inputStr = "";
  }
  #endif

  return 0;
}
