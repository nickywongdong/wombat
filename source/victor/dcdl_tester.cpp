/* ------------------------------------
   Axolotl Data Logging System Tester
   ------------------------------------
   Process that sets up the environment for data logging and spawns
   the OBDII data logging and dashcam logging processes.
*/

#include "dcomh.hpp"

#define PST -8
#define LOG_VOLUME "/media/nvidia/AXOLOTLDCV"

#define DEBUG

//#define KEYTEST
#define LOGTEST

using namespace std;

pid_t dcdpid = -1;
pid_t dldpid = -1;

void raiseShutdown() {
  int result = kill(dcdpid,SIGTERM);
  if(result != 0) {
    printf("Error: Failed to kill dashcam daemon.\n");
  }
  result = kill(dldpid,SIGTERM);
  if(result != 0) {
    printf("Error: Failed to kill data logging daemon.\n");
  }
}

/*
  Builds the save directory for both daemons.
  Returns the path to the directory that was created.
  /axolotl/data must exist in the user's home directory or this won't work.

  From here to final: instead of getHomeDir(), hardcode the mounted volume.
*/
string buildSaveDirectory() {
  // Getting info to build data storage directory
  int buildStatus = 2;
  string dirName = getHomeDir() + "/axolotl/data/axolotl_log_";
  // replace getHomeDir with LOG_VOLUME when on Axolotl

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
  passkeyHash = sha256hash(password);

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
  string newhash = sha256hash(password);
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
  string newhash = sha256hash("orangemonkeyeagle");
  string hashfilePath = sourceDir + "/hashkey";
  hashfile.open(hashfilePath, std::ofstream::trunc);
  if(hashfile.is_open()) {
    hashfile.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hashfile.close();
}

int main() {
  string inputStr;
  string homeDir = getPWD();

  // Testing password check and hashing
  #ifdef KEYTEST
  string readKey = "", toHashKey = "orangemonkeyeagle";
  ifstream checktruekey;
  checktruekey.open("hashkey");
  if(checktruekey.is_open()) {
    getline(checktruekey,readKey);
    printf("True key is: '%s'\n",readKey.c_str());
    printf("Comparable key is: '%s'\n",sha256hash(toHashKey).c_str());
  }
  checktruekey.close();
  printf("Status: %d\n",(readKey == "3453A0A7F1E111FC6E9E0E8071193DEA04EAF96CBFE4318539859876AA85FB15"));
  #endif

  // Data Logging Daemon Test
  #ifdef LOGTEST
  string loggingDirectory = buildSaveDirectory();
  if(loggingDirectory == "__fail_dir_build") {
    perror("Cannot build data logging directory");
  }
  else {
    char *args[] = {(char *)loggingDirectory.c_str(), NULL};
    dcdpid = fork();
    if (dcdpid == -1) {
      printf("Error spawning dashcam daemon... \n");
      exit(1);
    }
    else if (dcdpid == 0){
      execv("dld.axolotl", args);
    }
    else {
      while(1) {
        getline(cin,inputStr);
        if(inputStr == "q" | inputStr == "Q") {
          kill(dcdpid,SIGTERM);
          break;
        }
        else {
          inputStr = "";
        }
      }
    }
  }
  #endif

  return 0;
}
