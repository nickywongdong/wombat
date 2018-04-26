#include "viewer.h"
#include "ui_viewer.h"
#include<QFile>
#include<QString>
#include<QTextStream>
#include<QMessageBox>
#include<signal.h>

viewer::viewer(QWidget *parent, pid_t a, QString name) :
    QWidget(parent),
    ui(new Ui::viewer)
{
    filepath = name;
    dmid = a;
    ui->setupUi(this);
}

viewer::~viewer()
{
    delete ui;
}

void viewer::on_pushButton_clicked()
{
        kill(dmid,SIGUSR2);
        QFile file(filepath);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(0,"error", file.errorString());
        }
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
        file.close();
}
