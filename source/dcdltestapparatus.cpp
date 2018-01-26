// Axolotl Testing Apparatus for Both Daemons

#include "dcomh.h"

using namespace std;

pid_t dcdpid = -1;
pid_t dldpid = -1;

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

int main() {
  string inputStr;

  // Compile, Fork, and Exec (dcd only)
  char *const args[] = {NULL};
  dcdpid = fork();
  if (dcdpid == -1) {
    printf("Error spawning dashcam daemon... \n");
  }
  else if (dcdpid == 0){
    execv("dcd.axolotl", NULL);
    printf("Dashcam active!\n");
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
