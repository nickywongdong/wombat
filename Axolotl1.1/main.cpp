#include "mainwindow.h"
#include <QApplication>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
