/* ------------------------------------
   Axolotl Daemon Common Header
   ------------------------------------
   Header that specifies common methods for multiple Axolotl programs.

   Dependencies:
   - boost 1.66.0
*/

#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <clocale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include <boost/filesystem.hpp>

/*
  Gets and returns the non-privileged free memory of a specified volume in MiB.
  Parameter volumePath must be the path to said volume (i.e. /dev/disk0).
*/
double getAvailableMemory(std::string volumePath) {
  boost::filesystem::space_info volStats = boost::filesystem::space(volumePath);
  return (double)volStats.available/1048576;
}

/*
  Gets and returns the user's home directory as a string.
*/
std::string getHomeDir() {
  struct passwd *userPath = getpwuid(getuid());
  return userPath->pw_dir;
}
