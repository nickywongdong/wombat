/* ------------------------------------
   Daemon Launcher
   ------------------------------------
   Debugging apparatus.
   Sets up AP wifi with 802.11n protocol and then launches daemon manager.
*/

#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  chdir("wmanager");
  system("./set_ap_n");
  chdir("..");
  char *args[] = { NULL }
  execv("daemon_manager",args);
  return 0;
}
