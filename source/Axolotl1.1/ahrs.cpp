#include "ahrs.h"
#include "ui_ahrs.h"
#include<QFile>
#include<QString>
#include<QTextStream>
#include<QMessageBox>
#include<signal.h>

AHRS::AHRS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHRS)
{
    filepath = "/home/nvidia/axolotl/angles";
    ui->setupUi(this);
}

AHRS::~AHRS()
{
    delete ui;
}

void AHRS::on_pushButton_pressed()
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error", file.errorString());
    }
    QTextStream in(&file);
    ui->textBrowser_3->setText(in.readAll());
    file.close();
}

void AHRS::on_pushButton_2_pressed()
{
    system("cp /home/nvidia/axolotl/angles /home/nvidia/axolotl/zero_angles");
}
