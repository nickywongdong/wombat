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

MusicPage::MusicPage(QWidget *parent, pid_t m) :
    QDialog(parent),
    ui(new Ui::MusicPage)
{
    ui->setupUi(this);
    fopen = false;
    mopen = false;
    mpid = m;

}

MusicPage::~MusicPage()
{
    delete ui;
}


//button to pair with phone
void MusicPage::on_pushButton_2_clicked()
{
    std::string stop_command = "echo stop > /proc/" + std::to_string(mpid) + "/fd/0";
    system(stop_command.c_str());


    if(mopen)    kill(mpid,SIGINT);  //kill the previously spawned activity
    if(fopen)    kill(mpid,SIGINT);

    chdir("/home/nvidia/wombat/source/media_system/bluetooth_streaming/");
    int status;
    pid_t fml;
    fml = fork(
                );
    //execute script to pair with bluetooth device
    if(fml==0){
        execl("./bluetooth_pair.sh", "bluetooth_pair.sh", NULL);
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
    sleep(1);
    //system("pacmd load-module module-switch-on-connect");

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


}

void MusicPage::closeEvent(QCloseEvent *event){

    system("pulseaudio -k");    //close the stream upon exiting gui

    kill(mpid,SIGINT);
    kill(fmid,SIGTERM);
    event->accept();

}

void MusicPage::on_pushButton_pressed()
{
    system("pactl -- set-sink-volume 0 0%");
}


void MusicPage::on_horizontalSlider_sliderMoved(int position)
{
    std::string vol_command = "pactl -- set-sink-volume 0 " + std::to_string(position) + "%";
    system(vol_command.c_str());
}
