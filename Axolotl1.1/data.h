#ifndef DATA_H
#define DATA_H

#include <QWidget>

namespace Ui {
class Data;
}

class Data : public QWidget
{
    Q_OBJECT

public:
    explicit Data(QWidget *parent = 0);
    ~Data();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Data *ui;
};

#endif // DATA_H
