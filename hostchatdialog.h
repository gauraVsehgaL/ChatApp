#ifndef HOSTCHATDIALOG
#define HOSTCHATDIALOG
#include<QGridLayout>
#include<QPushButton>
#include<QLabel>
#include<QDialog>
#include<QLineEdit>
#include "server.h"
//namespace Ui {
//class hostchatdialog;
//}
class hostchatdialog:public QDialog
{
    Q_OBJECT
public:
    explicit hostchatdialog(QWidget *parent=0);
    QGridLayout *layout;
    QPushButton *host;
    QLabel *port;
    QLineEdit *porttohost;
    void hello();
public slots:
    void enablehosting();
};

#endif // HOSTCHATDIALOG

