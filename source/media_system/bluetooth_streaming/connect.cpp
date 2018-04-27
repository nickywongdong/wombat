#include <iostream>
#include <cstdlib>
#include <string>


//this program will run the shell script "install.sh" and connect the specified bluetooth device to allow bluetooth streaming
//bluetooth address must must be passed to program on the command line. 
//**program will assume that there will be arguments passed in

int main(int argc, char** argv){



	std::string command = "./install.sh";
	command = command + " "  + argv[1];
	//send bluetooth address as command line arguments to the shell script to process

    if (system( NULL )){
    	system(command.c_str());
    }



    return 0;
}
