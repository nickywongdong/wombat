// Axolotl Daemon Common Header

#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <clocale>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include <boost/filesystem.hpp>

// Gets and returns free memory of specified volume in MiB
double getAvailableMemory(std::string volume) {
  boost::filesystem::space_info volStats = boost::filesystem::space(volume);
  return (double)volStats.available/1048576;
}
