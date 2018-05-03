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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_MusicPage
{
public:
    QPushButton *pushButton_2;
    QLabel *fmLabel;
    QLabel *auxLabel;
    QPushButton *pushButton;
    QSlider *horizontalSlider;
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
        pushButton_2 = new QPushButton(MusicPage);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(80, 170, 201, 91));
        fmLabel = new QLabel(MusicPage);
        fmLabel->setObjectName(QStringLiteral("fmLabel"));
        fmLabel->setGeometry(QRect(216, 96, 161, 51));
        auxLabel = new QLabel(MusicPage);
        auxLabel->setObjectName(QStringLiteral("auxLabel"));
        auxLabel->setGeometry(QRect(216, 256, 161, 51));
        pushButton = new QPushButton(MusicPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 340, 201, 91));
        horizontalSlider = new QSlider(MusicPage);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(100, 470, 160, 29));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_3 = new QPushButton(MusicPage);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(470, 170, 201, 91));

        retranslateUi(MusicPage);

        QMetaObject::connectSlotsByName(MusicPage);
    } // setupUi

    void retranslateUi(QDialog *MusicPage)
    {
        MusicPage->setWindowTitle(QApplication::translate("MusicPage", "Dialog", 0));
        pushButton_2->setText(QApplication::translate("MusicPage", "Pair", 0));
        fmLabel->setText(QString());
        auxLabel->setText(QString());
        pushButton->setText(QApplication::translate("MusicPage", "Mute", 0));
        pushButton_3->setText(QApplication::translate("MusicPage", "Aux", 0));
    } // retranslateUi

};

namespace Ui {
    class MusicPage: public Ui_MusicPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPAGE_H
