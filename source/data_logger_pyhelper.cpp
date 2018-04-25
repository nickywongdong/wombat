/* ------------------------------------
   Axolotl Data Logger Python Helper
   ------------------------------------
   Execs the data_obd_logger.
*/

#include "dcomh.hpp"

#ifdef __linux__
#define OBD_ADAPTER_PATH "/home/nvidia/wombat/source/data_obd_logger.py"
#else
#define OBD_ADAPTER_PATH "/Gitdir/wombat/source/data_obd_logger.py"
#endif

using namespace std;

int main(int argc, char *argv[]) {
  string currPid = to_string(getpid()), loggingDirectory = argv[1];
  cout << getpid() << endl;
  string builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + loggingDirectory + " " + currPid;
  system(builtCommand.c_str());
  return 0;
}
