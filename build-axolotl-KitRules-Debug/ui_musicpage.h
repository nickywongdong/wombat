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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicPage
{
public:
    QPushButton *pushButton_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QLabel *pairLabel;
    QPushButton *pushButton_3;
    QLabel *mediaLabel;
    QLabel *fmLabel;
    QLabel *auxLabel;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSlider *horizontalSlider;

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
        stackedWidget = new QStackedWidget(MusicPage);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(360, 10, 841, 641));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        pairLabel = new QLabel(page_2);
        pairLabel->setObjectName(QStringLiteral("pairLabel"));
        pairLabel->setGeometry(QRect(-20, 150, 181, 71));
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(210, 160, 201, 91));
        mediaLabel = new QLabel(page_2);
        mediaLabel->setObjectName(QStringLiteral("mediaLabel"));
        mediaLabel->setGeometry(QRect(30, 440, 121, 51));
        stackedWidget->addWidget(page_2);
        fmLabel = new QLabel(MusicPage);
        fmLabel->setObjectName(QStringLiteral("fmLabel"));
        fmLabel->setGeometry(QRect(216, 96, 161, 51));
        auxLabel = new QLabel(MusicPage);
        auxLabel->setObjectName(QStringLiteral("auxLabel"));
        auxLabel->setGeometry(QRect(216, 256, 161, 51));
        pushButton = new QPushButton(MusicPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 340, 201, 91));
        pushButton_5 = new QPushButton(MusicPage);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(310, 390, 71, 61));
        pushButton_6 = new QPushButton(MusicPage);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(310, 310, 71, 61));
        horizontalSlider = new QSlider(MusicPage);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(100, 470, 160, 29));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(MusicPage);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MusicPage);
    } // setupUi

    void retranslateUi(QDialog *MusicPage)
    {
        MusicPage->setWindowTitle(QApplication::translate("MusicPage", "Dialog", 0));
        pushButton_2->setText(QApplication::translate("MusicPage", "Pair", 0));
        pairLabel->setText(QString());
        pushButton_3->setText(QApplication::translate("MusicPage", "Aux", 0));
        mediaLabel->setText(QString());
        fmLabel->setText(QString());
        auxLabel->setText(QString());
        pushButton->setText(QApplication::translate("MusicPage", "Mute", 0));
        pushButton_5->setText(QApplication::translate("MusicPage", "Down", 0));
        pushButton_6->setText(QApplication::translate("MusicPage", "Up", 0));
    } // retranslateUi

};

namespace Ui {
    class MusicPage: public Ui_MusicPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPAGE_H
