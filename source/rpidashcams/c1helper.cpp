#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
  sleep(10);
  system("raspivid -t 0 -w 1920 -h 1080 -fps 30 -g 5 -b 2000000 -vf -o - | gst-launch-1.0 --gst-debug=3 fdsrc ! h264parse ! video/x-h264, format=byte-stream ! rtph264pay ! udpsink host=192.168.8.1 port=9001");
  return 0;
}
