/********************************************************************************
** Form generated from reading UI file 'data.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_H
#define UI_DATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Data
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Data)
    {
        if (Data->objectName().isEmpty())
            Data->setObjectName(QStringLiteral("Data"));
        Data->resize(1280, 800);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(255, 158, 2, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        Data->setPalette(palette);
        pushButton = new QPushButton(Data);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 90, 161, 71));
        pushButton_2 = new QPushButton(Data);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 230, 151, 71));
        pushButton_3 = new QPushButton(Data);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(90, 400, 141, 61));

        retranslateUi(Data);

        QMetaObject::connectSlotsByName(Data);
    } // setupUi

    void retranslateUi(QWidget *Data)
    {
        Data->setWindowTitle(QApplication::translate("Data", "Form", 0));
        pushButton->setText(QApplication::translate("Data", "Clear Logs", 0));
        pushButton_2->setText(QApplication::translate("Data", "Change Password", 0));
        pushButton_3->setText(QApplication::translate("Data", "Reset Password", 0));
    } // retranslateUi

};

namespace Ui {
    class Data: public Ui_Data {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_H
