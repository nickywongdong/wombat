#include "musicpage.h"
#include "ui_musicpage.h"
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
#include <QWindow>
#include <QVBoxLayout>

MusicPage::MusicPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicPage)
{
    ui->setupUi(this);
    open = false;

}

MusicPage::~MusicPage()
{
    delete ui;
}

//button to open the FM Radio
void MusicPage::on_pushButton_clicked()
{
    system("pulseaudio -k");    //reset the pulseaudio stream

    if(open)    kill(mpid,SIGINT);  //kill before we spawn another one

    ui->auxLabel->setText("");
    ui->mediaLabel->setText("");
    ui->pairLabel->setText("");
    ui->fmLabel->setText("Opening FM Radio");

    ui->stackedWidget->setCurrentIndex(0);

    std::ifstream f;
    char c[256];
    std::string foo;

    mpid = fork();
        //chdir("/home/nvidia/Desktop/github/source/");
        if(mpid==0){
            execl("/usr/bin/gqrx", "gqrx", NULL);
        }
        else{
            chdir("/home/nvidia/wombat/");
        }



    chdir("/home/nvidia/wombat");
    snprintf(c, 256,"%s %d","bash getwindidbypid",(int)mpid);
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
    ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentWidget(widget);


    ui->fmLabel->setText("");
    open = true;

}

//button to pair with phone
void MusicPage::on_pushButton_2_clicked()
{

    system("pulseaudio -k");    //reset the pulseaudio stream

    if(open)    kill(mpid,SIGINT);  //kill the previously spawned activity


    ui->pairLabel->setText("Pairing with iPhone");
    ui->auxLabel->setText("");
    ui->mediaLabel->setText("");
    ui->fmLabel->setText("");
    system("/home/nvidia/Desktop/github/source/bluetooth_streaming/bluetooth_stream.sh");
    ui->pairLabel->setText("Paired with iPhone");
}

//button to enable aux
void MusicPage::on_pushButton_3_clicked()
{

    system("pulseaudio -k");    //reset the pulseaudio stream

    if(open)    kill(mpid,SIGINT);  //kill the previously spawned activity

    ui->auxLabel->setText("Enabling Aux");

    system("pacmd load-module module-loopback source=alsa_output.usb-0d8c_C-Media_USB_Audio_Device-00.analog-stereo sink=alsa_output.platform-3510000.hda.hdmi-stereo-extra1.monitor");
    system("pactl load-module module-loopback");



    ui->mediaLabel->setText("");
    ui->pairLabel->setText("");
    ui->fmLabel->setText("");

}

//button to open media player
void MusicPage::on_pushButton_4_clicked()
{
    system("pulseaudio -k");    //restart pulseaudio

    if(open)    kill(mpid,SIGINT);  //kill the previously spawned activity

    ui->auxLabel->setText("");
    ui->mediaLabel->setText("Opening Media Player");
    ui->pairLabel->setText("");
    ui->fmLabel->setText("");

    ui->stackedWidget->setCurrentIndex(0);

    std::ifstream f;
    char c[256];
    std::string foo;

    mpid = fork();
        chdir("/home/nvidia/Desktop/github/source/media_player");
        if(mpid==0){
            execl("/usr/bin/vlc", "vlc","--playlist-autostart","--loop","--playlist-tree","Music", "/media/nvidia/S", NULL);
        }
        else{
            chdir("/home/nvidia/wombat/");
        }



    chdir("/home/nvidia/wombat");
    snprintf(c, 256,"%s %d","bash getwindidbypid",(int)mpid);
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
    ui->stackedWidget->addWidget(widget);
    ui->stackedWidget->setCurrentWidget(widget);
    ui->mediaLabel->setText("");
    open=true;

}

void MusicPage::closeEvent(QCloseEvent *event){

    system("pulseaudio -k");    //close the stream upon exiting gui

    kill(mpid,SIGINT);
    kill(fmid,SIGTERM);
    event->accept();

}
