/* ------------------------------------
   Data Logger Python Helper
   ------------------------------------
   Execs the data_obd_logger.py script.
*/

#include "dcomh.hpp"

// Supply the path to the script, assuming everything's installed in the home directory
#ifdef __linux__
#define OBD_ADAPTER_PATH "/wombat/source/data_logging/data_obd_logger.py"
#else
#define OBD_ADAPTER_PATH "/Gitdir/wombat/data_logging/data_obd_logger.py"
#endif

using namespace std;

int main(int argc, char *argv[]) {
  string helper_pid = to_string(getpid());    // pass this pid to python script so it knows when to quit
  string logging_directory_path = argv[1];
  cout << getpid() << endl;
  string builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + logging_directory_path + " " + helper_pid;
  system(builtCommand.c_str());
  return 0;
}
