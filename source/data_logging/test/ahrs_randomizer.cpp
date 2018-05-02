#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

std::string createTimestamp() {
  time_t raw_time;
  time (&raw_time);

  struct tm *time_sample = localtime(&raw_time);
  std::string timestamp = asctime(time_sample);
  //std::cout << timestamp << std::endl;
  timestamp.pop_back();
  return timestamp;
}

int main() {
  for (int i=0; i < 8; i++) {
    std::string write_string = "@" + createTimestamp() + ",55,66,77\n";
    std::ofstream ahrs_write_file;
    ahrs_write_file.open("ahrs_log.csv", std::ofstream::out | std::ofstream::app);
    ahrs_write_file << write_string;
    ahrs_write_file.close();
    sleep(1);
  }
  return 0;
}
