#include "dialog.h"
#include "ui_dialog.h"
#include<QString>
#include<QObject>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
   // QWidget* mainwdg=new QWidget;
    layout=new QGridLayout;
    conne=new QPushButton;
    cance=new QPushButton;
    putip=new QLabel("enter ip to connect");
    putport=new QLabel("enter port to connect");
    ip=new QLineEdit;
    port=new QLineEdit;
    error=new QLabel("<i>Please check the ip and port address is correct and server is up running<i>");
    cance->setText("cancel");
    conne->setText("connect");
    //disable pushbutton connect until something is typed
    conne->setEnabled(false);
    nickname=new QLineEdit;
    nickname->setText("enter your nickname");
   // QObject::connect(nickname,SIGNAL(textChanged(QString)),nickname,SLOT(clear()));
    QObject::connect(cance,SIGNAL(clicked()),this,SLOT(close()));
    layout->addWidget(putip,0,0);
    layout->addWidget(ip,0,1);
    layout->addWidget(putport,1,0);
    layout->addWidget(port,1,1);
    layout->addWidget(conne,2,0);
    layout->addWidget(cance,2,1);
    layout->addWidget(nickname,3,0);
  //  layout->addWidget(error,3,0,2,2);
    this->setLayout(layout);
    QObject::connect(ip,SIGNAL(textChanged(QString)),this,SLOT(enableconnect()));
    QObject::connect(port,SIGNAL(textEdited(QString)),this,SLOT(enableconnect()));
    // QObject::connect(conne,SIGNAL(clicked()),this,SLOT(senddata()));
   // mainwdg->show();
}
void Dialog::enableconnect()
{
    if(ip->text()!="" && port->text()!="")
    {
        conne->setEnabled(true);
    }
    else
    {
        conne->setEnabled(false);
    }
}
void Dialog::displayerror()
{
    layout->addWidget(error,3,0,2,2);
}
Dialog::~Dialog()
{
    delete ui;
}
