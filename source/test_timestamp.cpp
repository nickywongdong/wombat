#include <iostream>
#include <string>
#include <time.h>

#include "dcomh.hpp"

#if defined(__linux__) && defined(LOG_VOLUME_INSTALLED)
#define LOG_VOLUME "/media/nvidia/AXOLOTLDCV"
#else
#define LOG_VOLUME axolotlFileSystem::getHomeDir()
#endif

using namespace std;

std::string createTimestamp() {
  string dirPrefix = "/axolotl/data/axolotl_log_", dirBase = LOG_VOLUME, dirName = dirBase + dirPrefix;

  time_t raw_time = time(NULL);
  struct tm *processed_time = localtime(&raw_time);
  string startYear = to_string(processed_time->tm_year+1900);
  string startMonth = to_string(processed_time->tm_mon+1);
  string startDay = to_string(processed_time->tm_mday);

  int startSecProcessed = processed_time->tm_sec;
  string startSec = to_string(startSecProcessed);
  if(startSecProcessed < 10) {
    startSec = "0" + startSec;    // ensures that seconds are always 2 digits
  }

  int startMinProcessed = processed_time->tm_min;
  string startMin = to_string(startMinProcessed);
  if(startMinProcessed < 10) {
    startMin = "0" + startMin;    // ensures that minutes are always 2 digits
  }

  int startHourProcessed = processed_time->tm_hour;
  string startHour = "" + to_string(startHourProcessed);
  if(startHourProcessed < 10) {
    startHour = "0" + startHour;    // ensures that hours are always 2 digits
  }

  // Assemble path
  dirName = dirName + startYear + "_" + startMonth + "_" + startDay + "_" + startHour + startMin + startSec;
  return dirName;
}

int main() {
  time_t raw_time;
  time (&raw_time);

  struct tm *time_sample = localtime(&raw_time);
  std::string timestamp = asctime(time_sample);

  timestamp.pop_back();
  std::cout << timestamp << "...." << std::endl;

  return 0;

}
