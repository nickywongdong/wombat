#include "dcomh.h"
#include <sys/statvfs.h>
#include <boost/filesystem.hpp>

// Adapt to using the boost library; currently bad bytes returned for macOS.

using namespace std;

int main() {
  struct statvfs currSysStats;
  if(statvfs("/Volumes/SD Transfer",&currSysStats) != 0) {
    printf("Failed to query for system info.\n");
  }
  else {
    printf("%lu Remaining Bytes!\n",currSysStats.f_bsize * currSysStats.f_bavail / (1048576));
  }
  return 0;
}
