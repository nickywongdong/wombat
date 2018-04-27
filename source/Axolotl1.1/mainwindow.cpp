#include <QWindow>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "musicpage.h"
#include "data.h"
#include "viewer.h"
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
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
    // system("sudo /home/nvidia/Desktop/wombat-victor-dev/source/wmanager/set_client.sh");
    // music pulling here
    system("sudo /home/nvidia/source/data_logging/wmanager/set_ap_n.sh");
    dmid = fork();
    chdir("/home/nvidia/wombat/source/data_logging/");
    if(dmid==0){
        execl("../source/daemon_launcher", "daemon_launcher", NULL);
    }
    else{
        chdir("/home/nvidia/wombat/");
    }

    nvid = fork();
    chdir("/home/nvidia/wombat/source/navigation/navit/");

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
    snprintf(c, 256,"%s %d","bash getwindidbypid > ./windowid.txt",(int)nvid);
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
    ui->tabWidget->addTab(new viewer(this, dmid),"error codes");
    ui->tabWidget->addTab(new viewer(this, dmid),"fuel economy");
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
        snprintf(c, 256,"%s %d","bash getwindidbypid > ./fmwindid.txt",(int)fmid);
        sleep(1);   //necessary
        system(c);
        f.open("./fmwindid.txt");
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
            //chdir("/home/nvidia/Desktop/github/source/media_player");
            chdir("/home/nvidia/wombat/source/media_system/media_player");
            if(mpid==0){
                execl("/usr/bin/vlc", "vlc", "--no-video", "--no-playlist-autostart","--loop","--playlist-tree",  "/media/nvidia/AXOLOTLDCV", "Music", NULL);
            }
            else{
                chdir("/home/nvidia/wombat/");
            }



        chdir("/home/nvidia/wombat");
        snprintf(c, 256,"%s %d","bash getwindidbypid > mpwindid.txt",(int)mpid);
        sleep(1);   //necessary
        system(c);
        f.open("./mpwindid.txt");
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
int status;
    kill(dmid,SIGINT);
    waitpid(dmid,&status,-1);
    kill(nvid,SIGINT);
    waitpid(nvid,&status,-1);
    kill(fmid,SIGINT);
    waitpid(fmid,&status,-1);
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}
