#include "musicpage.h"
#include "ui_musicpage.h"

MusicPage::MusicPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicPage)
{
    ui->setupUi(this);
}

MusicPage::~MusicPage()
{
    delete ui;
}

void MusicPage::on_pushButton_clicked()
{

}

void MusicPage::on_pushButton_2_clicked()
{

}

void MusicPage::on_pushButton_3_clicked()
{

}
