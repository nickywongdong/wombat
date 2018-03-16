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
#include<QStackedWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    system("sudo /home/nvidia/Desktop/wombat-victor-dev/source/wmanager/set_client.sh");
    // music pulling here
    system("sudo /home/nvidia/Desktop/wombat-victor-dev/source/wmanager/set_ap.sh");
    dmid = fork();
    chdir("/home/nvidia/wombat/source/");
    if(dmid==0){
        execl("../source/daemon_launcher", "daemon_launcher", NULL);
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
    std::string bar;
    std::string baz;
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
    //QVBoxLayout *layout = new QVBoxLayout();
    //layout->addWidget(widget);
    //this->setLayout(layout);
    ui->tabWidget->addTab(widget,"Navigation");
    ui->tabWidget->addTab(new Data(this, dmid),"Data");
    ui->tabWidget->addTab(new MusicPage(),"Media");

    fmid = fork();
            //chdir("/home/nvidia/Desktop/github/source/");
            if(fmid==0){
                execl("/usr/bin/gqrx", "gqrx", NULL);
            }
            else{
                chdir("/home/nvidia/wombat/");
            }



        chdir("/home/nvidia/wombat");
        snprintf(c, 256,"%s %d","bash getwindidbypid",(int)fmid);
        sleep(1);   //necessary
        system(c);
        f.open("./windowid.txt");
        std::getline(f,bar);
        f.close();
        windid = strtoull(bar.c_str(),NULL,16);


        QWindow *window1 = QWindow::fromWinId(windid);
        window1->setFlags(Qt::FramelessWindowHint);
        QWidget *widget1 = QWidget::createWindowContainer(window1);
        widget1->setParent(this);
        //QVBoxLayout *layout = new QVBoxLayout();
        //layout->addWidget(widget);
        //this->setLayout(layout);
        ui->tabWidget->addTab(widget1, "FM");


        mpid = fork();
            chdir("/home/nvidia/Desktop/github/source/media_player");
            if(mpid==0){
                execl("/usr/bin/vlc", "vlc","--loop","--playlist-tree","Music", "/media/nvidia/S", NULL);
            }
            else{
                chdir("/home/nvidia/wombat/");
            }



        chdir("/home/nvidia/wombat");
        snprintf(c, 256,"%s %d","bash getwindidbypid",(int)mpid);
        sleep(1);   //necessary
        system(c);
        f.open("./windowid.txt");
        std::getline(f,baz);
        f.close();
        windid = strtoull(baz.c_str(),NULL,16);


        QWindow *window2 = QWindow::fromWinId(windid);
        window2->setFlags(Qt::FramelessWindowHint);
        QWidget *widget2 = QWidget::createWindowContainer(window2);
        widget2->setParent(this);
        //QVBoxLayout *layout = new QVBoxLayout();
        //layout->addWidget(widget);
        //this->setLayout(layout);
        ui->tabWidget->addTab(widget2, "Media Player");

}

void MainWindow::closeEvent(QCloseEvent *event){

    kill(dmid,SIGINT);
    kill(nvid,SIGINT);
    kill(fmid,SIGINT);
    event->accept();

}

MainWindow::~MainWindow()
{
    delete ui;
}


