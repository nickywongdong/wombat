#include "ahrs.h"
#include "ui_ahrs.h"

AHRS::AHRS(QWidget *parent, pid_t a) :
    QWidget(parent),
    ui(new Ui::AHRS)
{
    dmid = a;
    ui->setupUi(this);
}

AHRS::~AHRS()
{
    delete ui;
}

void AHRS::on_pushButton_pressed()
{

}

void AHRS::on_pushButton_2_pressed()
{

}
