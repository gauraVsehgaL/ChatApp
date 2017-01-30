#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGridLayout>
#include<QTabWidget>
#include<QDebug>
#include<QWidget>
#include "client.h"
#include "server.h"
void function()
{
    for(int i=1;;i++)
    {
        qDebug()<<i;
    }
}
    MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        wdg=new QTabWidget;
        wdg->setTabsClosable(true);//now a cross on tabs; no action yet
        QObject::connect(wdg,SIGNAL(tabCloseRequested(int)),this,SLOT(closeatab(int)));
        //QObject::connect(wdg,SIGNAL(tabCloseRequested(int)),aclient,SLOT(disconnectchat()));
        ui->setupUi(this);
    }
    MainWindow::~MainWindow()
    {
    delete ui;
    }
    void MainWindow::closeatab(int index)
    {
        //if
        //aclient->disconnectchat();
        //else
        //aserver->stophosting();
        QList<QPushButton*> t=wdg->widget(index)->findChildren<QPushButton*>();//get the pushbutton which closes and press it
        if(t.count()==1)
        t[0]->clicked();//if its is client or server both connection stops
        wdg->removeTab(index);
    }
void MainWindow::on_actionHost_a_chat_triggered()
{
    qDebug()<<"in here";
    hostdialog=new hostchatdialog();
    hostdialog->setWindowTitle("host a chat");
    hostdialog->setModal(true);//cannot interact with previous window until this closed
    QObject::connect(hostdialog->host,SIGNAL(clicked()),this,SLOT(porttohost()));
    hostdialog->exec();
}
void MainWindow::on_actionJoin_a_chat_triggered()
{
    newdialog=new Dialog();
    newdialog->setWindowTitle("Join a chat");
    newdialog->setModal(true);
    qDebug()<< QObject::connect(newdialog->conne,SIGNAL(clicked()),this,SLOT(receivesocketaddress()));
    //
    newdialog->exec();
}
void MainWindow::porttohost()
{
    server *aserver=new server();
    qDebug()<<hostdialog->porttohost->text();
    aserver->temp=hostdialog->porttohost->text();
    aserver->port=hostdialog->porttohost->text().toLocal8Bit().data();
    if(aserver->basicwork())
    {
    hostdialog->close();
    wdg->addTab(aserver,tr("hosting"));
    setCentralWidget(wdg);
    //aserver->work();
    QFuture<void> t2=QtConcurrent::run(aserver,&server::work);
    }
    else
    {
        //cud not host
    }
}
void MainWindow::receivesocketaddress()
{
    client *aclient=new client;
//    aclient=new client;
    aclient->iptoconnect=newdialog->ip->text().toLocal8Bit().data();
    aclient->porti=newdialog->port->text().toLocal8Bit().data();
    if(aclient->prework()==0)//ie connected
    {
        qDebug()<<"connect ho gaya bhai";
     //now connect if connnected open a new tab to chat

        //now you should send the name of client

        strcpy(aclient->nickname,newdialog->nickname->text().toLocal8Bit().data());
//aclient->nickname="gaurav";
     //   qDebug()<<aclient->nickname;
        aclient->sendclientname(aclient->nickname);
     newdialog->close();
     wdg->addTab(aclient,tr("new chat"));
     setCentralWidget(wdg);//now show th ui
    /* aclient->startreceiveme();*/
     QFuture<void> t1=QtConcurrent::run(aclient,&client::receiveme);
    }
    else
    {
        newdialog->displayerror();
        qDebug()<<"cud not connect";
    }
}
void MainWindow::on_actionExit_triggered()
{
    close();   
}
void MainWindow::on_actionHow_to_use_this_triggered()
{

}
void MainWindow::on_actionAbout_triggered()
{

}
