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

#include "ahrs.h"
#include "ui_ahrs.h"
#include<QFile>
#include<QString>
#include<QTextStream>
#include<QMessageBox>
#include<signal.h>
#include <QTimer>
#include <iostream>

// AHRS::AHRS(QWidget *parent) :
//     QWidget(parent),
//     ui(new Ui::AHRS)
// {
//     filepath = "/home/nvidia/axolotl/angles";
//     ui->setupUi(this);
// }
//
// AHRS::~AHRS()
// {
//     delete ui;
// }
//
// void AHRS::on_pushButton_pressed()
// {
//     QFile file(filepath);
//     if(!file.open(QIODevice::ReadOnly)){
//         QMessageBox::information(0,"error", file.errorString());
//     }
//     QTextStream in(&file);
//     ui->textBrowser_3->setText(in.readAll());
//     file.close();
// }
//
// void AHRS::on_pushButton_2_pressed()
// {
//     system("cp /home/nvidia/axolotl/angles /home/nvidia/axolotl/zero_angles");
// }

double side_current_rot = 0.0, front_current_rot = 0.0;
int n = 0;

AHRS::AHRS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AHRS)
    {
        filepath = "/home/nvidia/axolotl/angles";
        ui->setupUi(this);

        // set up the vehicle side view image
//        QPixmap side_profile("/home/nvidia/wombat/source/profile.png");
//        QLabel side_profile_label();
//        side_profile_label.setPixmap(side_profile);
//        side_profile_label.show();

//        // set up the vehicle side view image
//        QPixmap front_image("/home/nvidia/wombat/source/front.png");
//        QLabel front_image_label();
//        front_image_label.setPixmap(front_image);
//        front_image_label.show();




        // // set up the vehicle side view image
        // QPixmap side_profile("profile.jpg");
        // QLabel side_profile_label();
        // side_profile_label.setPixmap(side_profile);
        // side_profile_label.show();
        QTimer *update_timer = new QTimer(this);
        connect(update_timer, SIGNAL(timeout()), this, SLOT(AHRS::update()));
        update_timer->start(1000);
    }

AHRS::~AHRS()
{
    delete ui;
}

void AHRS::update() {
    n++;
    std::cout << n << std::endl;
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
  side_current_rot = front_current_rot = 0.0;

//  QPixmap temp_pixmap(*side_profile_label->pixmap());
//  QMatrix rotation_matrix;
//  rotation_matrix.rotate(side_current_rot);
//  temp_pixmap = temp_pixmap.transformed(rotation_matrix);
//  side_profile_label->setPixmap(temp_pixmap);

//  QPixmap temp_pixmap_f(*front_image_label->pixmap());
//  QMatrix rotation_matrix_f;
//  rotation_matrix_f.rotate(front_current_rot);
//  temp_pixmap_f = temp_pixmap_f.transformed(rotation_matrix_f);
//  front_image_label->setPixmap(temp_pixmap_f);

  system("cp /home/nvidia/axolotl/calibrated_angles /home/nvidia/axolotl/zero_angles");
}
