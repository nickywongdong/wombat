#ifndef FORKBOMB_H
#define FORKBOMB_H
#include<QObject>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>


class test : public QObject{
    Q_OBJECT
public:
    explicit test (QObject* parent = 0) : QObject(parent){}
    Q_INVOKABLE int start_navit();
    Q_INVOKABLE int start_dm();
    Q_INVOKABLE int kill_dm();

private:
    pid_t dmid;
    pid_t nvid;
};


#endif // FORKBOMB_H
