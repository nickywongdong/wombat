#ifndef DATA_H
#define DATA_H

#include <QWidget>
#include <sys/types.h>
namespace Ui {
class Data;
}

class Data : public QWidget
{
    Q_OBJECT

public:
    explicit Data(QWidget *parent = 0, pid_t a=0);
    ~Data();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Data *ui;
    pid_t dmid;
};

#endif // DATA_H
