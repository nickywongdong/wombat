#ifndef MUSICPAGE_H
#define MUSICPAGE_H

#include <QDialog>

namespace Ui {
class MusicPage;
}

class MusicPage : public QDialog
{
    Q_OBJECT

public:
    explicit MusicPage(QWidget *parent = 0);
    ~MusicPage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MusicPage *ui;
};

#endif // MUSICPAGE_H
