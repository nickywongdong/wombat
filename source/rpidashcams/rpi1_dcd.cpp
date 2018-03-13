#include <iostream>
#include <cstdlib>
#include <pthread.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

pid_t camerahelper_pid;

int main(int argc, char **argv) {
  struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
  char buf[1024] = { 0 };
  int s, client, bytes_read;
  socklen_t opt = sizeof(rem_addr);

  // allocate socket
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  // bind socket to port 1 of the first available
  // local bluetooth adapter
  loc_addr.rc_family = AF_BLUETOOTH;
  loc_addr.rc_bdaddr = *BDADDR_ANY;
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
              camerahelper_pid = fork();
              if(obdLoggerPid == 0) {
                execv("c1helper",args);
              }
              waitpid(camerahelper_pid, &status, -1);
              camerahelper_pid = -5;
          }
          else if(buf[0] == 'p' || buf[0] == 'q'){
              if(camerahelper_pid > 1) {
                kill(camerahelper_pid,SIGKILL);
              }
              if(buf[0] == 'q') {
                break;
              }
          }
      }
  }

  // close connection
  close(client);
  close(s);

  return 0;
}
