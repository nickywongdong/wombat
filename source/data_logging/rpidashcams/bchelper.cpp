#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
  sleep(3);
  system("raspivid -t 0 -w 1920 -h 1080 -fps 30 -b 1000000 -vf -o - | gst-launch-1.0 -v fdsrc ! h264parse ! rtph264pay config-interval=1 pt=96 ! gdppay ! udpsink host=192.168.8.1 port=9003");
  return 0;
}
