#include <QWindow>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "musicpage.h"
#include "data.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<signal.h>
#include<string>
#include<QCloseEvent>
#include<QTabWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dmid = fork();
    chdir("/home/nvidia/wombat/source/");
    if(dmid==0){
        execl("../source/daemon_launcher", "daemon_manager", NULL);
    }
    else{
        chdir("/home/nvidia/wombat/");
    }

    nvid = fork();
    chdir("/home/nvidia/wombat/source/navit_build/navit/");

    if(nvid==0){
        execl("./navit", "navit", NULL);
    }
    else{
        chdir("/home/nvidia/wombat/");
    }

    char c[256];
    std::string foo;
    std::ifstream f;
    chdir("/home/nvidia/wombat");
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
    ui->tabWidget->addTab(widget,"Navigation");
    ui->tabWidget->addTab(new MusicPage(),"Music");
    ui->tabWidget->addTab(new Data(),"Data");
}

void MainWindow::closeEvent(QCloseEvent *event){

    kill(dmid,SIGINT);
    kill(nvid,SIGTERM);
    event->accept();

}

MainWindow::~MainWindow()
{
    delete ui;
}


