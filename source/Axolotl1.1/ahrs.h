#ifndef AHRS_H
#define AHRS_H

#include <QWidget>
#include <sys/types.h>
#include<QString>
#include<QFile>

namespace Ui {
class AHRS;
}

class AHRS : public QWidget
{
    Q_OBJECT

public:
    explicit AHRS(QWidget *parent = 0);
    ~AHRS();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::AHRS *ui;
    QString filepath;

};

#endif // AHRS_H
