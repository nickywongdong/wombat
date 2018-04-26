#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <sys/types.h>
#include<QString>
#include<QFile>
namespace Ui {
class viewer;
}

class viewer : public QWidget
{
    Q_OBJECT

public:
    explicit viewer(QWidget *parent = 0, pid_t a=0, QString name = "/home/nvidia/axolotl/defaultin.txt");
    ~viewer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewer *ui;
    pid_t dmid;
    QString filepath;
};

#endif // VIEWER_H
