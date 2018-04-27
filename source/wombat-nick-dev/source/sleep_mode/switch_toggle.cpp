#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <csignal>
#include "JetsonGPIO.h"


//gpio pins for output, and input:
jetsonTX2GPIONumber OUT = gpio296;
jetsonTX2GPIONumber IN1 = gpio481;
//later use
//jetsonTX2GPIONumber IN2;

int getkey();


int main(int argc, char *argv[]){

    std::cout << "Toggle Switch Testing" << std::endl;

    // Make the button and led available in user space
   	//we will use voltage as output pin for now
    //gpioExport(OUT) ;
    gpioExport(IN1) ;
    //gpio_request();
    //original directions:
    //gpioSetDirection(pushButton,inputPin) ;
    //gpioSetDirection(redLED,outputPin) ;
    //gpioSetDirection(OUT, outputPin);
    gpioSetDirection(IN1, inputPin);

    // Reverse the button wiring; this is for when the button is wired
    // with a pull up resistor
    // gpioActiveLow(pushButton, true);


    std::cout << "Please press the button! ESC key quits the program" << std::endl;

    unsigned int value = low;
    //int outputValue = low ;
    // set output value to low
    //gpioSetValue(OUT,low) ;
    while(getkey() != 27) {
        gpioGetValue(IN1, &value) ;
        // Useful for debugging
        // cout << "Input Value: " << value << endl;
        if ( value==high ) {

        	std::cout << "Pin is High " << std::endl;
        	system("sleep 1 ");
            //Switch is toggled on, tell Jetson to sleep:
            system("echo mem > /sys/power/state");
        }
    }

    std::cout << "Finished" << std::endl;
    //gpioUnexport(OUT);      // unexport the output pin
    gpioUnexport(IN1);      // unexport the input pin
    //gpioUnexport(IN2);
    return 0;
}

//seems to be a function to grab character from stdin
int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}