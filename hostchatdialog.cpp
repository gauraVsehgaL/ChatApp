#include<hostchatdialog.h>
#include"ui_dialog.h"
hostchatdialog::hostchatdialog(QWidget *parent):QDialog(parent)
{
    host=new QPushButton("host");
    port=new QLabel("enter port to host chat");
    porttohost=new QLineEdit;
    layout=new QGridLayout;
    layout->addWidget(porttohost,0,0);
    layout->addWidget(port,1,0);
    layout->addWidget(host,2,0,1,2);
    host->setEnabled(false);
    setLayout(layout);
    QObject::connect(porttohost,SIGNAL(textChanged(QString)),this,SLOT(enablehosting()));
}
void hostchatdialog::enablehosting()
{
    if(porttohost->text()!="")
        host->setEnabled(true);
    else
        host->setEnabled(false);
}


