/*******************************************************************************
*   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
*   Copyright (C) 2018 by Team Wombat
*   Victor Li <livic@oregonstate.edu>
*   Nick Wong <wongnich@oregonstate.edu>
*   Ryan Crane <cranery@oregonstate.edu>
*
*   This file is part of Axolotl.
*
*   Axolotl is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   Axolotl is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
*   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*******************************************************************************/

/* ------------------------------------
   Data Logging Authentication Functions
   ------------------------------------
   Defines functions that authenticate the user for black box clearing.
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
  string hash_file_path = string(getenv("HOME")) + "/axolotl/hashkey"; //normally run_directory + "/hashkey"
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
  string hash_file_path = string(getenv("HOME")) + "/axolotl/hashkey"; // normally run_directory + "/hashkey"
  hash_file.open(hash_file_path, std::ofstream::trunc);
  if(hash_file.is_open()) {
    hash_file.write((const char *)newhash.c_str(),(long)newhash.length());
  }
  hash_file.close();
}
