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
