/* ------------------------------------
   Axolotl Data Logging Authentication Functions
   ------------------------------------
   Defines functions that authenticate the user for data log clearing.
*/

#include "dcomh.hpp"
#include <sys/stat.h>

using namespace std;

/*
  Checks the supplied password against the stored password.
*/
bool checkPasswordCorrect(string password) {
  string truekey;
  ifstream truekeyf;
  string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey"; //normally run_directory + "/hashkey"
  truekeyf.open(hash_file_path);
  if(truekeyf.is_open()) {
    getline(truekeyf,truekey);
  }
  truekeyf.close();
  return (axolotlFileSystem::hash(password) == truekey);
}

/*
  Hashes a new password and changes old password hash with the new hash.
  Only if old password matches!
*/
bool changePassword(string checkPassword, string newPassword) {
  if(checkPasswordCorrect(checkPassword)) {
    ofstream hash_file;
    string newhash = axolotlFileSystem::hash(newPassword);
    string hash_file_path = string(getenv("HOME")) + "/axolotl/hashkey";    // normally run_directory + "/hashkey"
    hash_file.open(hash_file_path, std::ofstream::trunc);
    if(hash_file.is_open()) {
      hash_file.write((const char *)newhash.c_str(),(long)newhash.length());
    }
    hash_file.close();
    return true;
  }
  return false;
}

/*
  Resets password back to the original.
*/
void resetPassword() {
  ofstream hash_file;
  string newhash = axolotlFileSystem::hash("orangemonkeyeagle");
  string hash_file_path = string(getenv("HOME")) + "/wombat/source/data_logging/hashkey"; // normally run_directory + "/hashkey"
  hash_file.open(hash_file_path, std::ofstream::trunc);
  if(hash_file.is_open()) {
    hash_file.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hash_file.close();
}

// DEPRECATED
// /*
//   Wipes all data from the data logging system.
//   Will only destroy data if password matches.
// */
// void deleteData(string password) {
//   // Get true passkey hash from file
//   ifstream hash_file;
//   string truekeyHash = NULL;
//   string hash_file_path = string(getenv("HOME")) + "/axolotl/hashkey"; //normally run_directory + "/hashkey"
//   hash_file.open(hash_file_path);
//   if (hash_file.is_open()) {
//     getline(hash_file,truekeyHash);
//     hash_file.close();
//   }
//
//   // Delete the data only if password hashes match
//   if(axolotlFileSystem::hash(password) == truekeyHash) {
//     dataDeletionHandler();
//   }
//   #ifdef DEBUG
//   printf("Data deleted.\n");
//   #endif
// }
