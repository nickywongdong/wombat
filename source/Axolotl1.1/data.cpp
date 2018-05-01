#include "data.h"
#include "ui_data.h"
#include "/home/nvidia/wombat/source/data_logging/authentication.cpp"
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
    in = QInputDialog::getText(0, "Clear Data","Enter Password:", QLineEdit::Normal,"", &yes);
    std::string pass = in.toUtf8().constData();

    string truekey = "";
    ifstream truekeyf;
    //string hashfilePath = "/home/nvidia/wombat/source/data_logging/hashkey"; //normally runDirectory + "/hashkey"
    string hashfilePath = "/home/nvidia/axolotl/hashkey"; //normally runDirectory + "/hashkey"
    truekeyf.open(hashfilePath);
    if(truekeyf.is_open()) {
      getline(truekeyf,truekey);
    }
    truekeyf.close();

    if(axolotlFileSystem::hash(pass) == truekey){
        kill(dmid,SIGUSR1);
    }
    else{
        std::cout << "Password Incorrect: " << truekey << std::endl;
    }

}

void Data::on_pushButton_2_clicked()
{
    QString in;
    bool yes;
    in = QInputDialog::getText(0, "Change Password","Current Password:", QLineEdit::Normal,"", &yes);
    std::string oldpass = in.toUtf8().constData();
    in = QInputDialog::getText(0, "Change Password","New Password:", QLineEdit::Normal,"", &yes);

    std::string newpass = in.toUtf8().constData();
    changePassword(oldpass,newpass);
}

void Data::on_pushButton_3_clicked()
{
    resetPassword();
}
