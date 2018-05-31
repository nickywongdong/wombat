/*******************************************************************************
*   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
*   Copyright (C) 2018 by Team Wombat
*   Victor Li <livic@oregonstate.edu>
*   Nick Wong <wongnich@oregonstate.edu>
*   Ryan Crane <cranery@oregonstate.edu>
*
*   This file is part of Axolotl.
*
*   Axolotl is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   Axolotl is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
*   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*******************************************************************************/

/* ------------------------------------
   Daemon Manager
   ------------------------------------
   Entry point for black box system.
   Sets up the black box environment and manages all data logging processes.
*/

#include "dcomh.hpp"
#include <sys/stat.h>

#define DCDARG1 "./dashcamd"
#define DLDARG1 "./datad"

#define DEBUG

using namespace std;

pid_t dcdpid = -5, dldpid = -5;

string logging_directory, run_directory, log_volume, auto_delete, logging_directory_name;

/*
  Builds a logging directory from a path.
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
  Builds a logging directory for this boot cycle and returns success/failure.
  /axolotl/data must exist in the current log volume or this won't work.
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
  logging_directory_name = "axolotl_log_" + year_str + "_" + month_str + "_" + day_str + "_" + hour_str + minutes_str + seconds_str;

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
  Handles exit; kills daemons and frees their resources.
  QT: signal SIGINT to this process on system exit.
*/
void managerSigintHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  int status = 0;

  // kill and wait on termination of dashcam daemon
  if(!(dcdpid < 0)) {
    kill(dcdpid,SIGTERM);
  }
  waitpid(dcdpid, &status, -1);

  // kill and wait on termination of data logging daemon
  if(!(dldpid < 0)) {
    kill(dldpid,SIGTERM);
  }
  waitpid(dldpid, &status, -1);

  #ifdef RESET_WIFI
  chdir("wmanager");
  system("./set_client.sh");
  #endif

  // collate the logs into a master log
  string collate_csv_command = "python data_collator.py " + logging_directory;
  system(collate_csv_command.c_str());

  // exit cleanly
  exit(0);
}

/*
  Registers the kill signal handler with SIGINT.
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
*/
void deleteHandler(int signumber, siginfo_t *siginfo, void *pointer) {
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

  // new data deletion method
  // deletes everything but the currently active logging directory
  // bypasses data logging system stop, so we don't stop recording data
  #ifndef DELETION_METHOD_1

  char cwd_raw[10000];
  getcwd(cwd_raw, sizeof(cwd_raw));

  // get current directory and the base logging directory path
  string current_dir = string(cwd_raw);
  string base_dir = log_volume + "/axolotl/data";

  // create delete command
  string delete_command = "/bin/bash -O extglob -c 'rm -rf !(" + logging_directory_name + ")'";

  // enter base logging directory and delete all but current data log
  chdir(base_dir.c_str());
  cout << base_dir << endl;
  system("delete.sh");
  system(delete_command.c_str());
  chdir(current_dir.c_str());
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
  Registers the delete handler with SIGUSR1.
*/
void registerDeleteHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = deleteHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &dsa, NULL);
}

/*
  Signals the data logger DTC update/fuel economy analysis.
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

int main() {
  string input_str;
  run_directory = axolotlFileSystem::getPWD();

  // Clear this boot cycle's debug file
  system("rm -f ~/axolotl/debug");
  system("rm -f ~/axolotl/device_free");

  // Zero out speed and angle files
  system("echo \"0\" > ~/axolotl/vspeed");
  system("echo \"0\n0\n0\n\" > ~/axolotl/zero_angles");

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

      bool active = false;

      // Handle shutdown
      while(1) {
        // f.open("/sys/class/gpio/gpio481/value");
    	  // f >> i;
        //
        // // if state change on gpio pin, signal parent dashcam process
    	  // if(i == 1 && not(active)){
        //   if(rear_cam_bt_active) {
      	// 	  kill(getppid(),SIGBUS);
        //   }
    		//   active = true;
    		//   sleep(1);
    	  // }
    	  // else if(i == 0 && active){
        //   if(rear_cam_bt_active) {
      	// 	  kill(getppid(),SIGBUS);
        //   }
    		//   active = false;
    	  // 	  sleep(1);
    	  // }
    	  // f.close();
      }
    }
  }

  // manager waits on quit
  while(1) {
    getline(cin,input_str);
    pause();
  }

  return 0;
}
