#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <string>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

pid_t camerahelper_pid, bhelper_pid;

bool backupCameraActive = false;

int main(int argc, char **argv) {
  struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
  bdaddr_t ANY_RC_ADDR = {0, 0, 0, 0, 0, 0};
  char buf[1024] = { 0 };
  int s, client, bytes_read;
  socklen_t opt = sizeof(rem_addr);

  // allocate socket
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // bind socket to port 1 of the first available
  // local bluetooth adapter
  loc_addr.rc_family = AF_BLUETOOTH;
  loc_addr.rc_bdaddr = ANY_RC_ADDR;
  loc_addr.rc_channel = (uint8_t) 1;
  bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

  // put socket into listening mode
  listen(s, 1);

  // accept one connection
  client = accept(s, (struct sockaddr *)&rem_addr, &opt);

  ba2str( &rem_addr.rc_bdaddr, buf );
  fprintf(stderr, "accepted connection from %s\n", buf);
  memset(buf, 0, sizeof(buf));

  // read data from dashcam logger
  while(1){
      bytes_read = read(client, buf, sizeof(buf));
      char *args[] = { NULL };
      int status;
      if( bytes_read > 0 ) {
          printf("received [%s]\n", buf);
          if(buf[0] == 's'){
            if (camerahelper_pid < 1) {
              camerahelper_pid = fork();
              if(camerahelper_pid == 0) {
                execv("c1helper",args);
              }
            }
          }
          else if(buf[0] == 'b') {
            backupCameraActive = !backupCameraActive;
            if(backupCameraActive) {
              bhelper_pid = fork();
              if(bhelper_pid == 0) {
                execv("bchelper",args);
              }
              else {
                sleep(5); // for FMVSS
                system("killall bchelper");
                system("pkill -f port=9003");
                if(bhelper_pid > 1) {
                  kill(bhelper_pid,SIGKILL);
                  waitpid(bhelper_pid, &status, -1);
                  bhelper_pid = -5;
                }
              }
            }
          }
          else if ((buf[0] == 'p') || (buf[0] == 'q')) {
              if(camerahelper_pid > 1) {
                system("killall raspivid");
                system("killall gst-launch-1.0");
                kill(camerahelper_pid,SIGKILL);
                waitpid(camerahelper_pid, &status, -1);
                camerahelper_pid = -5;
                system("killall c2helper");
              }
              if(buf[0] == 'q') {
                printf("Quit signal received.\n");
              }
          }
      }
  }

  // close connection
  close(client);
  close(s);

  return 0;
}
