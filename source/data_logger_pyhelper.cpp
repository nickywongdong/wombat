#include "dcomh.hpp"

#define OBD_ADAPTER_PATH "/wombat/source/data_obd_logger.py"

using namespace std;

int main(int argc, char *argv[]) {
  string currPid = to_string(getpid()), loggingDirectory = argv[1];
  cout << getpid() << endl;
  string builtCommand = "python " + axolotlFileSystem::getHomeDir() + OBD_ADAPTER_PATH + " snapshot " + loggingDirectory + " " + currPid;
  system(builtCommand.c_str());
  return 0;
}
