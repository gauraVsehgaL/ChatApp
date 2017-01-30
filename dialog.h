#ifndef DIALOG_H
#define DIALOG_H
#include "client.h"
#include<QGridLayout>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include <QDialog>
#include<QDebug>
namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QGridLayout *layout;//=new QGridLayout;
    QPushButton *conne;//=new QPushButton;
    QPushButton *cance;//=new QPushButton;
    QLabel *error;
    QLabel *putip;//=new QLabel("enter ip to connect");
    QLabel *putport;//=new QLabel("enter port to connect");
    QLineEdit *ip;//=new QLineEdit;
    QLineEdit *port;//=new QLineEdit;
    QLineEdit *nickname;
public slots:
    void displayerror();
    void enableconnect();
void senddata()
{
 //   client *obj=new client();
   // obj->prework();//if connects show connected and create a tab for chat???????
   // socketaddress obj=new socketaddress;
    //obj.ip=ip->text();
    //obj.port=port->text();
    qDebug()<<"yeah";
    qDebug()<<ip->text();
    qDebug()<<port->text();
}
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
