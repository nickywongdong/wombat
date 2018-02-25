#include <QWindow>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<signal.h>
#include<string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pid_t nvid;
    nvid = fork();
    chdir("/home/nvidia/wombat/source/navit-build/navit/");

    if(nvid==0){
        execl("./navit", "navit", NULL);
    }
    else{
        chdir("/home/nvidia/untitled/");
    }
    char c[256];
    std::string foo;
    std::ifstream f;
    chdir("/home/nvidia/Downloads");
    snprintf(c, 256,"%s %d","bash getwindidbypid",(int)nvid);
    sleep(1);   //necessary
    system(c);
    f.open("./windowid.txt");
    std::getline(f,foo);
    f.close();
    unsigned long long int windid;
    windid = strtoull(foo.c_str(),NULL,16);
    QWindow *window = QWindow::fromWinId(windid);
    window->setFlags(Qt::FramelessWindowHint);
    QWidget *widget = QWidget::createWindowContainer(window);
    widget->setParent(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(widget);
    this->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
