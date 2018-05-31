/*******************************************************************************
*   Axolotl -- Open-Source Infotainment and Black Box for NVIDIA Jetson TX2
*   Copyright (C) 2018 by Team Wombat
*   Victor Li <livic@oregonstate.edu>
*   Nick Wong <wongnich@oregonstate.edu>
*   Ryan Crane <cranery@oregonstate.edu>
*
*   This file is part of Axolotl.
*
*   Axolotl is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   Axolotl is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Axolotl.  If not, see <http://www.gnu.org/licenses/>.
*   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*******************************************************************************/

#include "data.h"
#include "ui_data.h"
#include "/home/nvidia/wombat/source/data_logging/authentication.cpp"
#include <QString>
#include<QInputDialog>
#include<signal.h>
#include <fstream>
#include <iostream>

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

    // Check if the vehicle is moving, and prevent options from appearing if it is
    ifstream s_file;
    s_file.open("/home/nvidia/axolotl/vspeed");
    int vspeed = 0;
    if(s_file.is_open()) {
      std::string vspeed_str;
      s_file >> vspeed_str;
      s_file.close();
      vspeed = atoi(vspeed_str.c_str());
    }

    if(vspeed == 0) {
      system("dbus-send --type=method_call --dest=org.onboard.Onboard /org/onboard/Onboard/Keyboard org.onboard.Onboard.Keyboard.Show");
      in = QInputDialog::getText(0, "Clear Data","Enter Password:", QLineEdit::Normal,"", &yes);
      system("dbus-send --type=method_call --dest=org.onboard.Onboard /org/onboard/Onboard/Keyboard org.onboard.Onboard.Keyboard.Hide");
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
}

void Data::on_pushButton_2_clicked()
{
    QString in;
    bool yes;
    system("dbus-send --type=method_call --dest=org.onboard.Onboard /org/onboard/Onboard/Keyboard org.onboard.Onboard.Keyboard.Show");
    in = QInputDialog::getText(0, "Change Password","Current Password:", QLineEdit::Normal,"", &yes);
    std::string oldpass = in.toUtf8().constData();

    string truekey = "";
    ifstream truekeyf;
    //string hashfilePath = "/home/nvidia/wombat/source/data_logging/hashkey"; //normally runDirectory + "/hashkey"
    string hashfilePath = "/home/nvidia/axolotl/hashkey"; //normally runDirectory + "/hashkey"
    truekeyf.open(hashfilePath);
    if(truekeyf.is_open()) {
      getline(truekeyf,truekey);
    }
    truekeyf.close();
    if(axolotlFileSystem::hash(oldpass) == truekey){
        in = QInputDialog::getText(0, "Change Password","New Password:", QLineEdit::Normal,"", &yes);
        std::string newpass = in.toUtf8().constData();
        changePassword(oldpass,newpass);
    }
    system("dbus-send --type=method_call --dest=org.onboard.Onboard /org/onboard/Onboard/Keyboard org.onboard.Onboard.Keyboard.Hide");
}

void Data::on_pushButton_3_clicked()
{
    resetPassword();
}
