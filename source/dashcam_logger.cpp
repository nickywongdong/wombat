/* ------------------------------------
   Axolotl Dashcam Daemon
   ------------------------------------
   Background process managed by Axolotl;
   logs camera data from dashcam and backup camera.
*/

#include "dcomh.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define FRONT_CAM_BT_ADDR "B8:27:EB:FE:1C:65"
#define REAR_CAM_BT_ADDR "iunnoyet"

using namespace std;

string loggingDirectory;
bool loggingActive = true;

pid_t dchelper0_pid = -5, dchelper1_pid = -5;

void sendBluetoothCommand(string bluetoothAddress, char command) {
  struct sockaddr_rc addr = { 0 };
  int s, status;
  char dest[18] = bluetoothAddress.c_str();    //Bluetooth Address of device to connect to
  char input; //reading input from keyboard
  char buf[64];

  // allocate a socket
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( dest, &addr.rc_bdaddr );

  // connect to server
  status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

  // send a message
  if (status == 0) {
          status = write(s, command, 1);    //send 1 char to server
  }
  else if (status < 0) {
    perror("error in sending data");
  };

  close(s);
}

/*
  Records a chunk of video and saves to disk.
  Must be passed the bluetooth address of the respective dashcam and the TCP
  port the Jetson is receiving the stream at.
  Port 9001: front dashcam
  Port 9002: rear dashcam
  Port 9003: backup camera
*/
void record(string bluetoothAddress, int cameraPort) {
  //printf("Recording...\n");
  //sleep(10);
  //printf("Recording complete. Saving to file.\n");

  sendBluetoothCommand(bluetoothAddress,'s');

  string sysCmd = "gst-launch-1.0 -v udpsrc port=" + to_string(cameraPort) + " ! gdpdepay ! rtph264depay ! avdec_h264 ! autovideosink sync=false";

  system(sysCmd.c_str());
}

/*
  Constantly loops, calling record().
*/
void cameraLooper() {
  clock_t timer1;
  while(1) {
    if(loggingActive) {
      dchelper0_pid = fork();
      if(dchelper0_pid == 0) {
        if (axolotlFileSystem::getAvailableMemory(loggingDirectory) > 2048) {
          record(FRONT_CAM_BT_ADDR,9001);
        }
        else {
          dchelper1_pid = fork();
          if(dchelper1_pid == 0) {
            //record(REAR_CAM_BT_ADDR,9002);
          }
          else {

          }
        }
      }
    }
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
  int status;
  if((dchelper0_pid != -5) && (dchelper0_pid > 1)) {
    kill(dchelper0_pid,SIGKILL);
    waitpid(dchelper0_pid, &status, -1);
  }
  dchelper0_pid = -5;
  /*if((dchelper1_pid != -5) && (dchelper0_pid > 1)) {
    kill(dchelper1_pid,SIGKILL);
    waitpid(dchelper1_pid, &status, -1);
  }
  dchelper1_pid = -5;*/

  sendBluetoothCommand(FRONT_CAM_BT_ADDR,'q');
  //sendBluetoothCommand(REAR_CAM_BT_ADDR,'q');
}

/*
  Registers the toggle handler with SIGTERM.
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

  registerToggleOffHandler();
  registerToggleOnHandler();
  registerKillCamerasHandler();
  cameraLooper();

  return 0;
}
