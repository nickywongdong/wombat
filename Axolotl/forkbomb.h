#ifndef FORKBOMB_H
#define FORKBOMB_H
#include<QObject>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
class test : public QObject{
    Q_OBJECT
public:
    explicit test (QObject* parent = 0) : QObject(parent){}
    Q_INVOKABLE int start_a_thing();
};

#endif // FORKBOMB_H
