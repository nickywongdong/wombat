#include<forkbomb.h>
#include<cstring>

int test::start_navit(){
    nvid = fork();
    int cd = 0;
    cd = chdir("/home/nvidia/wombat/source/navit-build/navit/");

    if(nvid==0){
        execl("./navit", "navit", NULL);
        return 0;
    }
    else{
        cd = chdir("/home/nvidia/wombat/build-Axolotl-JetsonTX2-Debug");
        return cd;
    }
}

int test::start_dm(){
    dmid = fork();

    if(dmid==0){
        execl("../source/daemon_launcher", "daemon_manager", NULL);
        return 0;
    }
    else{
        return 1;
    }
}

int test::kill_dm(){
    return kill(dmid,SIGINT);
}
