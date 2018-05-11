/* ------------------------------------
   Axolotl Daemon Common Header
   ------------------------------------
   Header that specifies common methods for multiple Axolotl programs.

   Dependencies:
   - boost 1.66.0
   - CryptoPP 6.0.0
*/

#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <clocale>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

#include <boost/filesystem.hpp>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

/*
  Defines for byte, based on compilation environment.
*/
#ifdef __linux__
#define BYTE byte   // for Linux compilation
#else
#define BYTE CryptoPP::byte   // compiling on Windows and macOS
#endif

class axolotlFileSystem {
  public:
    /*
      Gets and returns the non-privileged free memory of a specified volume in MiB.
      Parameter volumePath must be the path to said volume (i.e. /dev/disk0).
    */
    static double getAvailableMemory(std::string volumePath) {
      boost::filesystem::space_info volStats = boost::filesystem::space(volumePath);
      return (double)volStats.available/1048576;
    }

    /*
      Gets and returns the user's home directory as a string.
    */
    static std::string getHomeDir() {
      struct passwd *userPath = getpwuid(getuid());
      return userPath->pw_dir;
    }

    /*
      Gets and returns the present working directory.
      Used to determine current path of source for running executables.
    */
    static std::string getPWD() {
      char pwd[2048];
      getcwd(pwd,sizeof(pwd));
      return (std::string)pwd;
    }

    /*
      Applies a SHA256 hash to a string and returns the hash'd string.
      Used to check password entry for data deletion...
      ...as well as writing new hashes to file.
    */
    static std::string hash(std::string s) {
      // Salt and hash
      std::string hashedPass, passSalt = "thequickbrownfoxjumpsoverthelazydog";
      CryptoPP::SHA256 passwordHash;
      BYTE passwordDigest[CryptoPP::SHA256::DIGESTSIZE];
      passwordHash.CalculateDigest(passwordDigest,(const BYTE *)s.c_str(),s.size());

      // Encode into human-readable string via hex
      CryptoPP::HexEncoder hashEncoder;
      CryptoPP::StringSink *hashStringSink = new CryptoPP::StringSink(hashedPass);
      hashEncoder.Attach(hashStringSink);
      hashEncoder.Put(passwordDigest,sizeof(passwordDigest));
      hashEncoder.MessageEnd();

      // Return the string hash
      return hashedPass;
    }
};
