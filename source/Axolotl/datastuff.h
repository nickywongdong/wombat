#ifndef DATASTUFF_H
#define DATASTUFF_H

#include<QObject>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<QString>

class DataStuff : public QObject{
    Q_OBJECT
public:
    explicit DataStuff (QObject* parent = 0) : QObject(parent){}
    Q_INVOKABLE int Query(QString);

private:
    QString password = "12345";
    void delete_logs();
};

#endif // DATASTUFF_H
