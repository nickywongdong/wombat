#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/types.h>
#include<QTabWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *);
    pid_t dmid;
    pid_t nvid;
    pid_t fmid;
    pid_t mpid;
    pid_t swid;
};

#endif // MAINWINDOW_H
