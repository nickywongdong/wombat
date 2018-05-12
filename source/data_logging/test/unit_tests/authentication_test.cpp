#include "../../dcomh.hpp"

using namespace std;

int main() {
  string truehash = "C2E1550B1B0002A0F2248ADC5A730589EE6AE31ABFE54F132ECB0480282EEF6E";
  if (axolotlFileSystem::hash("orangemonkeyeagle") == truehash) {
    cout << "AUTHENTICATION_TEST: Hash success against string" << endl;
  }
  else {
    cout << "AUTHENTICATION_TEST: Hash failure; please check library install" << endl;
  }

  if (axolotlFileSystem::hash("orangemonkeyeagle123123") == axolotlFileSystem::hash("orangemonkeyeagle123123")) {
    cout << "AUTHENTICATION_TEST: Hash success against another hash" << endl;
  }
  else {
    cout << "AUTHENTICATION_TEST: Hash failure; please check library install" << endl;
  }

  return 0;
}
