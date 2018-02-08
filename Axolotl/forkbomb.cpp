#include<forkbomb.h>
#include<cstring>

int test::start_a_thing(){
    int foo = 1;
    foo = fork();

    if(foo==0){
        execl("/usr/bin/firefox", "firefox", NULL);
        return 0;
    }
    else{
        return 1;
    }
}
