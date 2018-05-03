/********************************************************************************
** Form generated from reading UI file 'ahrs.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AHRS_H
#define UI_AHRS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AHRS
{
public:
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *AHRS)
    {
        if (AHRS->objectName().isEmpty())
            AHRS->setObjectName(QStringLiteral("AHRS"));
        AHRS->resize(1280, 800);
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
        AHRS->setPalette(palette);
        textBrowser = new QTextBrowser(AHRS);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 50, 330, 231));
        textBrowser_2 = new QTextBrowser(AHRS);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(350, 50, 330, 231));
        textBrowser_3 = new QTextBrowser(AHRS);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(690, 50, 330, 231));
        pushButton = new QPushButton(AHRS);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(300, 310, 99, 27));
        pushButton_2 = new QPushButton(AHRS);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(640, 310, 99, 27));

        retranslateUi(AHRS);

        QMetaObject::connectSlotsByName(AHRS);
    } // setupUi

    void retranslateUi(QWidget *AHRS)
    {
        AHRS->setWindowTitle(QApplication::translate("AHRS", "Form", 0));
        pushButton->setText(QApplication::translate("AHRS", "Refresh", 0));
        pushButton_2->setText(QApplication::translate("AHRS", "Zero", 0));
    } // retranslateUi

};

namespace Ui {
    class AHRS: public Ui_AHRS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AHRS_H
