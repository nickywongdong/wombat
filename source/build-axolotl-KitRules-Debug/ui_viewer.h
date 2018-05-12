/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewer
{
public:
    QTextBrowser *textBrowser;
    QPushButton *pushButton;

    void setupUi(QWidget *viewer)
    {
        if (viewer->objectName().isEmpty())
            viewer->setObjectName(QStringLiteral("viewer"));
        viewer->resize(1280, 800);
        textBrowser = new QTextBrowser(viewer);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(236, 30, 600, 300));
        pushButton = new QPushButton(viewer);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(311, 370, 450, 150));
        QFont font;
        font.setPointSize(36);
        pushButton->setFont(font);

        retranslateUi(viewer);

        QMetaObject::connectSlotsByName(viewer);
    } // setupUi

    void retranslateUi(QWidget *viewer)
    {
        viewer->setWindowTitle(QApplication::translate("viewer", "Form", 0));
        pushButton->setText(QApplication::translate("viewer", "Refresh", 0));
    } // retranslateUi

};

namespace Ui {
    class viewer: public Ui_viewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
