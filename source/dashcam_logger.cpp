/* ------------------------------------
   Axolotl Dashcam Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs camera data from dashcam and backup camera.
*/

#include "dcomh.hpp"

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define FRONT_CAM_BT_ADDR "B8:27:EB:FE:1C:65"
#define REAR_CAM_BT_ADDR "iunnoyet"
#define FRONT_CAMERA_HELPER_NAME "./front_cam_helper"
#define REAR_CAMERA_HELPER_NAME "./rear_cam_helper"
#define BACKUP_CAMERA_HELPER_NAME "./backup_cam_helper"

#define FRONT_CAMERA_PORT "9001"
#define REAR_CAMERA_PORT "9002"
#define BACKUP_CAMERA_PORT "9003"

#define COMMAND_RECORD "r"
#define COMMAND_WATCH "w"

using namespace std;

string loggingDirectory;
bool loggingActive = true, backup_cam_active = false;

pid_t dchelper0_pid = -5, dchelper1_pid = -5, bcamera_pid = -5;

int fdcfd, rdcfd;

/*
  Makes a bluetooth connection, storing info for accessing into a file descriptor by address.
*/
void connectBluetooth(string bluetoothAddress, int *fd) {
  struct sockaddr_rc addr = { 0 };
  int status;
  char *dest = (char *)bluetoothAddress.c_str();    // connect to bt device @ given bluetooth address

  // allocate bluetooth socket
  *fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set connection parameters struct
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( dest, &addr.rc_bdaddr );

  // connect to the raspberrypi, saving connection into a global file descriptor
  status = connect(*fd, (struct sockaddr *)&addr, sizeof(addr));
}

/*
  Use an active bluetooth file descriptor to send a command.
*/
void sendBluetoothCommand(int fd, char command) {
  int status;
  if (status == 0) {
    status = write(fd, &command, 1);
  }
  else if (status < 0) {
    perror("Problem sending to RaspberryPi: ");
  }
}

/*
  Mananges all logging.
*/
void cameraLooper() {
  char *args[] = {(char *)FRONT_CAMERA_HELPER_NAME, (char *)FRONT_CAMERA_PORT, (char *)COMMAND_RECORD, (char *)loggingDirectory.c_str(), NULL};
  while(1) {
    if(loggingActive) {
      dchelper0_pid = fork();
      if(dchelper0_pid == 0) {
        if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 2048) {
          sendBluetoothCommand(fdcfd,'s');
          execv("record",args);
        }
        else {
          //dchelper1_pid = fork();
          if(dchelper1_pid == 0) {
            //record(REAR_CAM_BT_ADDR,9002);
          }
          else {

          }
        }
      }
    }
    pause();
    /*while(1) {
      // wait and do nothing...
    }*/
  }
}

/*
  Kills all of the gstreamer processes, dashcam helpers, and record programs.
*/
void killallHelpers() {
  int status;
  system("killall record");
  system("killall gst-launch-1.0");

  if((dchelper0_pid != -5) && (dchelper0_pid > 1)) {
    kill(dchelper1_pid,SIGKILL);
    waitpid(dchelper1_pid, &status, -1);
  }
  dchelper0_pid = -5;

  if((dchelper1_pid != -5) && (dchelper1_pid > 1)) {
    kill(dchelper1_pid,SIGKILL);
    waitpid(dchelper1_pid, &status, -1);
  }
  dchelper1_pid = -5;
}

/*
  Kills all cameras, send kill command to the raspberrypi.
  Closes file descriptors to bluetooth sockets and exits cleanly.
*/
void killCamerasHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  printf("IMA FIRIN MAH LAZOR\n");

  sendBluetoothCommand(fdcfd,'q');
  //sendBluetoothCommand(rdcfd,'q');

  killallHelpers();

  close(fdcfd);
  close(rdcfd);
  exit(0);
}

/*
  Registers the kill handler with SIGTERM.
*/
void registerKillCamerasHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = killCamerasHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &dsa, NULL);
}

/*
  Turns logging off.
*/
void toggleOffHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = false;
  sendBluetoothCommand(fdcfd,'p');
  killallHelpers();
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
  Turns logging on.
*/
void toggleOnHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = true;
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
  Starts the backup camera process, forcing it to display over the UI.
*/
void startBackupCameraHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  char *args[] = {(char *)BACKUP_CAMERA_HELPER_NAME, (char *)BACKUP_CAMERA_PORT, (char *)COMMAND_WATCH, (char *)loggingDirectory.c_str(), NULL};
  sendBluetoothCommand(rdcfd,'b');
  execv("record",args);
}

/*
  Registers the kill handler with SIGBUS.
*/
void registerStartBackupCameraHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = startBackupCameraHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGBUS, &dsa, NULL);
}

int main(int argc, char *argv[]) {
  // Ensure that a logging directory has been provided and bind it

  loggingDirectory = argv[1];

  connectBluetooth(FRONT_CAM_BT_ADDR, &fdcfd);
  registerToggleOffHandler();
  registerToggleOnHandler();
  registerKillCamerasHandler();
  cameraLooper();

  return 0;
}
