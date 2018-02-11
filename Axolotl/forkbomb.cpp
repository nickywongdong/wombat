#include<forkbomb.h>
#include<cstring>

int test::start_navit(){
    int foo = 1;
    foo = fork();

    if(foo==0){
        execl("../source/navit-build/navit/navit", "navit", NULL);
        return 0;
    }
    else{
        return 1;
    }
}

int test::start_dm(){
    int foo = 1;
    foo = fork();

    if(foo==0){
        execl("../source/daemon_manager", "daemon_manager", NULL);
        return 0;
    }
    else{
        return 1;
    }
}
