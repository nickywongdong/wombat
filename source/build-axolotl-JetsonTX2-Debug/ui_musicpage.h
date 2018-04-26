/********************************************************************************
** Form generated from reading UI file 'musicpage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICPAGE_H
#define UI_MUSICPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MusicPage
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *MusicPage)
    {
        if (MusicPage->objectName().isEmpty())
            MusicPage->setObjectName(QStringLiteral("MusicPage"));
        MusicPage->resize(1280, 800);
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
        MusicPage->setPalette(palette);
        pushButton = new QPushButton(MusicPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 90, 131, 61));
        pushButton_2 = new QPushButton(MusicPage);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 250, 131, 61));
        pushButton_3 = new QPushButton(MusicPage);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(80, 410, 131, 61));

        retranslateUi(MusicPage);

        QMetaObject::connectSlotsByName(MusicPage);
    } // setupUi

    void retranslateUi(QDialog *MusicPage)
    {
        MusicPage->setWindowTitle(QApplication::translate("MusicPage", "Dialog", 0));
        pushButton->setText(QApplication::translate("MusicPage", "FM", 0));
        pushButton_2->setText(QApplication::translate("MusicPage", "Bluetooth", 0));
        pushButton_3->setText(QApplication::translate("MusicPage", "Aux", 0));
    } // retranslateUi

};

namespace Ui {
    class MusicPage: public Ui_MusicPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPAGE_H
