#include <iostream>
#include <cstdlib>

int main() {
  while(1) {
    system("gst-launch-1.0 -e v4l2src do-timestamp=true ! video/x-h264,width=1920,height=1080,framerate=30/1 ! h264parse ! rtph264pay config-interval=1 ! gdppay ! udpsink host=192.168.8.1 port=9001");
  }
  return 0;
}
