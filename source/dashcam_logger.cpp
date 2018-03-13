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
#define FRONT_CAMERA_PORT "9001"

using namespace std;

string loggingDirectory;
bool loggingActive = true;

pid_t dchelper0_pid = -5, dchelper1_pid = -5;

int s;

void connectBluetooth1(string bluetoothAddress) {
  struct sockaddr_rc addr = { 0 };
  int status;
  char *dest = (char *)bluetoothAddress.c_str();    //Bluetooth Address of device to connect to

  // allocate a socket
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( dest, &addr.rc_bdaddr );

  // connect to server
  status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
}

void sendBluetoothCommand(int fd, char command) {
  int status;

  // send a message
  if (status == 0) {
    status = write(fd, &command, 1);    //send 1 char to server
  }
  else if (status < 0) {
    perror("error in sending data");
  }
}

/*
  Constantly loops, calling record().
*/
void cameraLooper() {
  clock_t timer1;
  char *args[] = {(char *)FRONT_CAMERA_HELPER_NAME, (char *)FRONT_CAMERA_PORT, NULL};
  if(loggingActive) {
    dchelper0_pid = fork();
    if(dchelper0_pid == 0) {
      if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 2048) {
        sendBluetoothCommand(s,'s');
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
  while(1) {
    // do nothing...
  }
}

/*
  Turns logging off.
*/
void toggleOffHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  loggingActive = false;
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
  Turns logging on.
*/
void killCamerasHandler(int signumber, siginfo_t *siginfo, void *pointer) {
  printf("IMA FIRIN MAH LAZOR\n");
  int status;
  sendBluetoothCommand(s,'q');
  kill(dchelper0_pid,SIGKILL);
  waitpid(dchelper0_pid, &status, -1);
  dchelper0_pid = -5;
  /*if((dchelper1_pid != -5) && (dchelper0_pid > 1)) {
    kill(dchelper1_pid,SIGKILL);
    waitpid(dchelper1_pid, &status, -1);
  }
  dchelper1_pid = -5;*/
  //sendBluetoothCommand(REAR_CAM_BT_ADDR,'q');
  close(s);
  exit(0);
}

/*
  Registers the handler with SIGTERM.
*/
void registerKillCamerasHandler() {
  static struct sigaction dsa;
  memset(&dsa, 0, sizeof(dsa));
  dsa.sa_sigaction = killCamerasHandler;
  dsa.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &dsa, NULL);
}

int main(int argc, char *argv[]) {
  // Ensure that a logging directory has been provided and bind it

  loggingDirectory = argv[1];

  connectBluetooth1(FRONT_CAM_BT_ADDR);
  registerToggleOffHandler();
  registerToggleOnHandler();
  registerKillCamerasHandler();
  cameraLooper();

  return 0;
}
