#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
  sleep(5);
  system("raspivid -t 999999 -w 1080 -h 720 -fps 30 -b 2000000 -o - | gst-launch-1.0 -v fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! gdppay ! udpsink host=192.168.8.1 port=9003 sync=false async=false");
  return 0;
}
