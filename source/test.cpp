#include <cstdio>
#include <cstdlib>
#include <sys/statvfs.h>
#include <boost/filesystem.hpp>

// Adapt to using the boost library; currently bad bytes returned for macOS.

using namespace std;
using namespace boost::filesystem;

int main() {
  struct statvfs currSysStats;
  //boost::filesystem::space_info sysStats = boost::filesystem::space(".");


  space_info s;
  s = space("/Volumes/SD Transfer/");
  printf("%f Remaining GiB!\n",(float)s.available/1073741824);///(1048576));

  if(statvfs("/Volumes/SD Transfer/new.txt",&currSysStats) != 0) {
    printf("Failed to query for system info.\n");
  }
  else {
    printf("%lu Remaining Bytes...!\n",currSysStats.f_bsize * currSysStats.f_bfree);
  }
  return 0;
}
