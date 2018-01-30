// Axolotl Testing Apparatus for Both Daemons
// This code can then be added to Axolotl startup

#include "dcomh.hpp"

#define PST -8

using namespace std;

pid_t dcdpid = -1;
pid_t dldpid = -1;

// Signal shutdown to daemons
void raiseShutdown() {
  int result = kill(dcdpid,SIGQUIT);
  if(result != 0) {
    printf("Error: Failed to kill dashcam daemon.\n");
  }
  result = kill(dldpid,SIGQUIT);
  if(result != 0) {
    printf("Error: Failed to kill data logging daemon.\n");
  }
}

// Builds a directory that the logging system will save data to
// Returns the path to the directory that was created
// ~/axolotl/data MUST exist or this won't work.
string buildSaveDirectory() {
  // Getting current working directory
  char *pwd;
  long pwdlen;
  char *pwdp = getcwd(pwd,(size_t)pwdlen);
  printf("%s\n",pwdp);

  // Getting info to build data storage directory
  int buildStatus = 2;
  struct passwd *userPath = getpwuid(getuid());
  string userHomeDir = userPath->pw_dir;
  string dirName = userHomeDir + "/axolotl/data/axolotl_log_";

  // Create directory name based off of date
  time_t startTime = time(NULL);
  struct tm *startTimeAsUTC = gmtime(&startTime);
  string startYear = to_string(startTimeAsUTC->tm_year+1900);
  string startMonth = to_string(startTimeAsUTC->tm_mon+1);
  string startDay = to_string(startTimeAsUTC->tm_mday);
  string startMin = to_string(startTimeAsUTC->tm_min);
  long startHourProcessed = startTimeAsUTC->tm_hour+PST;
  if(startHourProcessed < 0) {
    startHourProcessed += 24;   // adjusts if UTC-8 is earlier than UTC midnight
  }
  string startHour = "" + to_string(startHourProcessed);
  if(startHourProcessed < 10) {
    startHour = "0" + startHour;    // ensures that all times are 4 digits
  }
  dirName = dirName + startYear + "_" + startMonth + "_" + startDay + "_" + startHour + startMin;

  // Build the directory; return name if success or predefined error if failed
  buildStatus = mkdir((const char *)dirName.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
  if(buildStatus != 0) {
    dirName = "__fail_dir_build";
  }
  return dirName;
}

int main() {
  // Variables for Testing Apparatus
  string inputStr;
  string loggingDirectory = buildSaveDirectory();
  if(loggingDirectory == "__fail_dir_build") {
    perror("Cannot build data logging directory");
    printf("~/axolotl/data may not exist.\n");    // not needed for *final* version, which will hardcode a storage volume.
    exit(1);
  }

  // Forking Dashcam Daemon
  char *args[] = {(char *)loggingDirectory.c_str(), NULL};
  dcdpid = fork();
  if (dcdpid == -1) {
    printf("Error spawning dashcam daemon... \n");
  }
  else if (dcdpid == 0){
    execv("dcd.axolotl", args);
  }
  else {
    while(1) {
      getline(cin,inputStr);
      if(inputStr == "q" | inputStr == "Q") {
        kill(dcdpid,SIGINT);
        break;
      }
      else {
        inputStr = "";
      }
    }
  }

  return 0;
}
