#include "datastuff.h"



void DataStuff::delete_logs(){
    system("rm -rf /home/nvidia/axolotl/data/*");
}


int DataStuff::Query(QString x){
    if(x==password){
        delete_logs();
        return 0;
    }else{
        return 1;
    }
}
