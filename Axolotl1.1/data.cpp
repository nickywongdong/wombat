#include "data.h"
#include "ui_data.h"

Data::Data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Data)
{
    ui->setupUi(this);
}

Data::~Data()
{
    delete ui;
}

void Data::on_pushButton_clicked()
{

}
