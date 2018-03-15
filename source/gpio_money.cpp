#include<iostream>
#include<fstream>
#include<signal.h>
#include<unistd.h>


int main(){
using namespace std;
ifstream f;
int i;
bool streaming = false;

while(true){
	f.open("/sys/class/gpio/gpio298/value");
	f >> i;
	printf("%i and... %i\n",getppid(),getpid());
	if(i == 1 && not(streaming)){
		kill(getppid(),SIGBUS);
		//cout << i <<"\n";
		streaming = true;
		sleep(1);
	}
	else if(i == 0 && streaming){
		kill(getppid(),SIGBUS);
		//cout << i << "\n";
		streaming = false;
		sleep(1);
	}
	f.close();
}

}
