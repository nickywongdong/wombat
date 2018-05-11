#ifndef MUSICPAGE_H
#define MUSICPAGE_H

#include <QDialog>
#include <sys/types.h>
#include<unistd.h>

namespace Ui {
class MusicPage;
}

class MusicPage : public QDialog
{
    Q_OBJECT

public:
    explicit MusicPage(QWidget *parent = 0, pid_t m=getpid());
    ~MusicPage();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_pressed();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MusicPage *ui;
    void closeEvent(QCloseEvent *);
    pid_t mpid;
    pid_t fmid;
    bool fopen;
    bool mopen;
};

#endif // MUSICPAGE_H
