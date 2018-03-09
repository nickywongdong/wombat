#include "data.h"
#include "ui_data.h"
#include "/home/nvidia/Desktop/wombat-victor-dev/source/daemon_manager.cpp"
#include <QString>
#include<QInputDialog>
#include<signal.h>

Data::Data(QWidget *parent, pid_t a) :
    QWidget(parent),
    ui(new Ui::Data)
{
    dmid = a;
    ui->setupUi(this);
}

Data::~Data()
{
    delete ui;
}

void Data::on_pushButton_clicked()
{
    QString in;
    bool yes;
    in = QInputDialog::getText(0, "Challenge","Password:", QLineEdit::Normal,"", &yes);
    std::string pass = in.toUtf8().constData();
    if(checkPasswordCorrect(pass)){
        kill(dmid,SIGUSR1);
    }
    else{
        std::cout<<pass<<" get good\n";
    }

}

void Data::on_pushButton_2_clicked()
{
    QString in;
    bool yes;
    in = QInputDialog::getText(0, "Challenge"," Old Password:", QLineEdit::Normal,"", &yes);
    std::string oldpass = in.toUtf8().constData();
    in = QInputDialog::getText(0, "Challenge"," New Password:", QLineEdit::Normal,"", &yes);

    std::string newpass = in.toUtf8().constData();
    changePassword(oldpass,newpass);
}

void Data::on_pushButton_3_clicked()
{
    resetPassword();
}
