/* ------------------------------------
   Axolotl Data Logging System Tester
   ------------------------------------
   Process that sets up the environment for data logging and spawns
   the OBDII data logging and dashcam logging processes.
*/

#include "dcomh.hpp"

#ifdef __linux__
#define LOG_VOLUME "/media/nvidia/AXOLOTLDCV"   // external HDD must be named "AXOLOTLDCV"
#else
#define LOG_VOLUME axolotlFileSystem::getHomeDir()
#endif

#define DCDARG1 "./dashcamd"
#define DLDARG1 "./datad"
#define PST -8

#define DEBUG
#define KEYTEST
#define LOGTEST

using namespace std;

pid_t dcdpid = -5, dldpid = -5;

string loggingDirectory;

/*
  Builds the save directory for both daemons.
  Returns the path to the directory that was created.
  /axolotl/data must exist in the user's home directory or this won't work.

  From here to final: instead of axolotlFileSystem::getHomeDir(), hardcode the mounted volume.
*/
string buildSaveDirectory() {
  // Getting info to build data storage directory
  int buildStatus = 2;
  string dirName = LOG_VOLUME + "/axolotl/data/axolotl_log_";

  // create the base axolotl data directory if it doesn't exist
  system("mkdir -p ~/axolotl/data");

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

  // Return name if success or error if false
  if(buildStatus != 0) {
    dirName = "__fail_dir_build";
  }
  return dirName;
}

/*
  Wipes all data from the data logging system.
  Will not destroy data as part of THIS boot cycle.
  Will only destroy data if password matches.
*/
void deleteData(string password, string sourceDir) {
  // Get true passkey hash from file
  ifstream hashfile;
  string truekeyHash = NULL, passkeyHash = NULL;
  string hashfilePath = sourceDir + "/hashkey";
  hashfile.open(hashfilePath);
  if (hashfile.is_open()) {
    getline(hashfile,truekeyHash);
    hashfile.close();
  }

  // Hash the provided password
  passkeyHash = axolotlFileSystem::hash(password);

  // Delete the data only if password hashes match
  if(passkeyHash == truekeyHash) {

  }
  #ifdef DEBUG
  printf("Data deleted.\n");
  #endif
}

/*
  Hashes a new password and changes old password hash with the new hash.
*/
void changePassword(string password, string sourceDir) {
  ofstream hashfile;
  string newhash = axolotlFileSystem::hash(password);
  string hashfilePath = sourceDir + "/hashkey";
  hashfile.open(hashfilePath, std::ofstream::trunc);
  if(hashfile.is_open()) {
    hashfile.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hashfile.close();
}

/*
  Resets password back to the original.
*/
void resetPassword(string sourceDir) {
  ofstream hashfile;
  string newhash = axolotlFileSystem::hash("orangemonkeyeagle");
  string hashfilePath = sourceDir + "/hashkey";
  hashfile.open(hashfilePath, std::ofstream::trunc);
  if(hashfile.is_open()) {
    hashfile.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hashfile.close();
}

/*
  Checks the supplied password against the stored password.
*/
bool checkPasswordCorrect(string inPassword) {
  string truekey;
  ifstream truekeyf;
  truekeyf.open("hashkey");
  if(truekeyf.is_open()) {
    getline(truekeyf,truekey);
  }
  truekeyf.close();
  return (axolotlFileSystem::hash(inPassword) == truekey);
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
void registerSigHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = managerSigintHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGINT, &dsa, NULL);
}

int main() {
  string inputStr;
  string homeDir = axolotlFileSystem::getPWD();

  // Registering signal handler
  registerSigHandler();

  // Testing password check and hashing
  #ifdef KEYTEST
  printf("Checking true key: %i",checkPasswordCorrect("orangemonkeyeagle"));
  #endif

  // Data Logging Daemon Test
  #ifdef LOGTEST
  string loggingDirectory = buildSaveDirectory();
  if(loggingDirectory == "__fail_dir_build") {
    perror("Cannot build data logging directory");
  }
  else {
    char *args[] = {(char *)DLDARG1, (char *)loggingDirectory.c_str(), NULL};

    // forking data logging daemon
    dldpid = fork();
    if (dldpid == -1) {
      printf("Error spawning data logging daemon... \n");
    }
    else if (dldpid == 0){
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
        execv("dashcamd", args2);
      }
      else {
        printf(" ");
      }
    }
    
    // manager waits on quit
    while(1) {
      getline(cin,inputStr);
      if(inputStr == "q" | inputStr == "Q") {
        break;
      }
      else {
        inputStr = "";
      }
    }

  }
  #endif

  return 0;
}
