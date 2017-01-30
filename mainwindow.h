#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPushButton>
#include <QMainWindow>
#include"dialog.h"
#include"hostchatdialog.h"
#include "client.h"
#include<QThread>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   // QPushButton *btn1;
   // QWidget *wdg;
    Dialog* newdialog;//join a new chat
     hostchatdialog* hostdialog;//host a new chat
    //client *aclient;
    // client *aclient;
    QString ipp,portt;
    QTabWidget *wdg;
     QThread workerThread;
QThread t;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void startreceiveme();
private slots:
    void receivesocketaddress();
    void on_actionHost_a_chat_triggered();
    void on_actionJoin_a_chat_triggered();
    void on_actionExit_triggered();
    void on_actionHow_to_use_this_triggered();
    void on_actionAbout_triggered();
    void porttohost();
private:
    Ui::MainWindow *ui;
public slots:
    void closeatab(int index);
};
#endif // MAINWINDOW_H
