#include "musicpage.h"
#include "ui_musicpage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <string>
#include <QCloseEvent>
#include <QTabWidget>
#include <QStackedWidget>
#include <QWindow>
#include <QVBoxLayout>

MusicPage::MusicPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicPage)
{
    ui->setupUi(this);
    fopen = false;
    mopen = false;


}

MusicPage::~MusicPage()
{
    delete ui;
}

//button to open the FM Radio
void MusicPage::on_pushButton_clicked()
{
    /*system("pulseaudio -k");    //reset the pulseaudio stream

    if(mopen)    {
        kill(mpid,SIGINT);  //kill the previously spawned activity
        mopen = false;
    }
    if(fopen)    ui->stackedWidget->setCurrentIndex(0);
    else{

    ui->auxLabel->setText("");
    ui->mediaLabel->setText("");
    ui->pairLabel->setText("");
    ui->fmLabel->setText("Opening FM Radio");



    std::ifstream f;
    char c[256];
    std::string foo;

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
    ui->stackedWidget->addWidget(widget);
    //ui->stackedWidget->setCurrentWidget(widget);

    ui->stackedWidget->setCurrentIndex(0);
    ui->fmLabel->setText("");
    fopen = true;
    }*/

}

//button to pair with phone
void MusicPage::on_pushButton_2_clicked()
{

    system("pulseaudio -k");    //reset the pulseaudio stream
    //sleep(5);

    if(mopen)    kill(mpid,SIGINT);  //kill the previously spawned activity
    if(fopen)    kill(mpid,SIGINT);

    ui->pairLabel->setText("Pairing with device...");
    ui->auxLabel->setText("");
    ui->mediaLabel->setText("");
    ui->fmLabel->setText("");

    //chdir("/home/nvidia/Desktop/github/source/bluetooth_streaming/");
    chdir("/home/nvidia/wombat/source/media_system/bluetooth_streaming/");
    int status;
    pid_t fml;
    fml = fork(
                );
    if(fml==0){
        execl("./test2.sh", "test2.sh", NULL);
    }
    else{
        waitpid(fml, &status,0);
    }
    //system("./test.sh");
    //system("./bluetooth_streaming.sh");

    //system("/home/nvidia/Desktop/github/source/bluetooth_streaming/test.sh");
    //system("/home/nvidia/Desktop/github/source/bluetooth_streaming/load_modules.sh");
    //sleep(5);
    //system("pacmd load-module module-loopback source=bluez_source.70_70_0D_87_4D_D4 sink=alsa_output.platform-3510000.hda.hdmi-stereo-extra1");
    sleep(1);
    system("pacmd load-module module-loopback");
    ui->pairLabel->setText("Paired with device");
    sleep(1);
    ui->pairLabel->setText("");

}

//button to enable aux
void MusicPage::on_pushButton_3_clicked()
{

    system("pulseaudio -k");    //reset the pulseaudio stream

    if(mopen)    kill(mpid,SIGINT);  //kill the previously spawned activity
    if(fopen)    kill(mpid,SIGINT);
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


    if(fopen)    {
        kill(fmid,SIGINT);
        fopen=false;
    }
    if(mopen)    ui->stackedWidget->setCurrentIndex(1);
    ui->auxLabel->setText("");
    ui->mediaLabel->setText("Opening Media Player");
    ui->pairLabel->setText("");
    ui->fmLabel->setText("");



    std::ifstream f;
    char c[256];
    std::string foo;

 /*   mpid = fork();
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
    //QVBoxLayout *layout = new QVBoxLayout();
    //layout->addWidget(widget);
    //this->setLayout(layout);
    ui->stackedWidget->addWidget(widget);
    ui->mediaLabel->setText("");
    ui->stackedWidget->setCurrentIndex(1);
    mopen=true;
*/
}

void MusicPage::closeEvent(QCloseEvent *event){

    system("pulseaudio -k");    //close the stream upon exiting gui

    kill(mpid,SIGINT);
    kill(fmid,SIGTERM);
    event->accept();

}
