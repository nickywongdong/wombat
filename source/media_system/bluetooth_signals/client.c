#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:D8:59:7D";    //Bluetooth Address of device to connect to
    char input; //reading input from keyboard
    char buf[64];

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send a message
    if( status == 0 ) {
        while(true){        //persistent data transfer
            do{
                scanf("%c", &input);        //read from keyboard input
            } while(input != 'l' | input != 'r');
            buf[0] = input;
            status = write(s, buf, 1);    //send 1 char to server
        }
    }

    if( status < 0 ) perror("error in sending data");

    close(s);
    return 0;
}