#include "client.h"
#include<QGridLayout>
#include<QPushButton>
#include<QDebug>
#include<QWidget>
//#include<thread>
void client::setclientui()
{
    //create ui for the client
   QGridLayout *lay=new QGridLayout;
   QPushButton *btn=new QPushButton("oh yeah!");
   outputbox=new QTextEdit;
   inpbox=new QLineEdit;
   disconnect=new QPushButton;
   disconnect->setText("Disconnect");
   lay->addWidget(disconnect,0,2);
   (lay)->addWidget(outputbox,0,0,3,1);
   (lay)->addWidget(inpbox,4,0);
   (outputbox)->setReadOnly(true);//so that user cannot edit what it is receiving
  // avi=new QPushButton;
  // (&lay)->addWidget(avi,5,0);
//   QObject::connect(avi,SIGNAL(clicked()),this,SLOT(receiveme()));
   // outputbox->append("bye");
  // outputbox->append("hello");
   setLayout(lay);
}
void client::disconnectchat()
{
    qDebug()<<"in disconnectchat";
    ::close(sockfd);
    inpbox->setEnabled(false);
    outputbox->setEnabled(false);
}
client::client()
{
    //create ui for the client
   setclientui();
   strcpy(nickname,"\0");
   QObject::connect(inpbox,SIGNAL(returnPressed()),this,SLOT(sendme()));
   QObject::connect(disconnect,SIGNAL(clicked()),this,SLOT(disconnectchat()));
//   receiveme();
   //  qRegisterMetaType<client>("client");
}
void client::outputmessagereceived()
{
    receivebuf[numbytes]='\0';
       QString a=QString::fromLocal8Bit(receivebuf);
   //  qDebug()<<receivebuf;
   //  qDebug()<<a;
     outputbox->append(a);
     char *begin = &buf[0];
     char *end = begin + sizeof(buf);
     std::fill(begin, end, 0);
    //memset(receivebuf,sizeof(receivebuf),NULL);
  /*  moveToThread(&thread);
    connect(&thread,SIGNAL(started()),this,SLOT(receiveme()));
    thread.start();*/
}
void* client::get_in_addr(struct sockaddr *sa)
{
        if(sa->sa_family==AF_INET)
            return &(((struct sockaddr_in*)sa)->sin_addr);
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
void client::sendclientname(char  name[])
{
    qDebug()<<strlen(name);
 if(send(sockfd,name,strlen(name)+1,0)==-1)
 {
     qDebug()<<"naya navela client side";
 }
}
void client::sendme()
{
    QString tempi=(inpbox)->text().trimmed();
  //  qDebug()<<"s0   "<<inpbox->text().count();
    if(tempi.isEmpty())
        return;
    //  qDebug()<<"pahuch gaya be";
    whatistobesent=(inpbox)->text();
    //qDebug()<<inpbox->text().toLocal8Bit().data();
  //  qDebug()<<"s   "<<whatistobesent;
    strcpy(buf,whatistobesent.toLocal8Bit().data());
   // buf[]='\0';
//    qDebug()<<"s1  "<<buf;
  //  qDebug()<<"s3   "<<whatistobesent.count()<<sizeof(buf);
//    qDebug()<<"s3  "<<sizeof(whatistobesent.toLocal8Bit().data());
  //  qDebug()<<"s4  "<<sizeof(whatistobesent);
    //qDebug()<<buf;
 //   numbytes=whatistobesent.count();
 (inpbox)->clear();
    if ((temp = send(sockfd, buf,whatistobesent.count(),0)) == -1)
        {
            qDebug()<<"9";
            perror("send");
            exit(1);
        }
}
int client::prework()
{
 memset(&hints,0,sizeof(hints));
    hints.ai_family=AF_UNSPEC;//can be ipv4 or ipv6
    hints.ai_socktype=SOCK_STREAM;
    //above we filled the criteria of socket we need
    //nowwe will try to get suchh address to which we can connect
    if((rv=getaddrinfo(iptoconnect,porti,&hints,&serviceinfo)))
    {
        fprintf(stderr,"getaddrinfo: %s\n", gai_strerror(rv));
       // return 1;
    }
   // connectme();
    //if getaddrinfo did'nt fail we must have got valid addresses in form of linked list
    //and we will connect to the first we can
    for(iterator=serviceinfo;iterator!=NULL;iterator=iterator->ai_next)
    {
        //try to create a socket
        if((sockfd=socket(iterator->ai_family,iterator->ai_socktype,iterator->ai_protocol))==-1)
        {
            //error
         //   qDebug()<<"7";
            perror("client: socket");
            //check for next address
            continue;
        }
        //else we were able to create a socket
        //now try to connect
        if(::connect(sockfd,iterator->ai_addr,iterator->ai_addrlen)==-1)
        {
           // qDebug()<<"8";
            //could not connect
            ::close(sockfd);
            perror("client:connect");
            //try for next address
            continue;
        }
        //else we were able to connect too
        //now no longer do we need to check next address,get the hell out of here!!!
        break;
    }
    //check if all addresses finished and we cud not create a socket or could
    //not connect to a socket
    if(iterator==NULL)
    {
        //sad!!!!!
        fprintf(stderr,"client :failed to connect\n");
        return 2;
    }
    inet_ntop(iterator->ai_family,get_in_addr((struct sockaddr *)iterator->ai_addr),s,sizeof(s));
    printf("client: connecting to server %s\n:",s);
    freeaddrinfo(serviceinfo);//now free the list of addresses
  //  someshit();
    //std::thread(&client::receiveme(),this);
    //  sendme();
/*
    //we are connected and we can communicate with server
    if ((temp = send(sockfd, "You either die a hero or live long enough to see yourself become the villain",90,0)) == -1)
        {
        //qDebug()<<"9";
            perror("send");
            exit(1);
        }
  */    //  buf[numbytes] = '\0';
      //  printf("client: received '%s'\n",buf);
        //close(sockfd);

    return 0;//successful
}
void client::someshit()
{

}
void client::receiveme()
{
  //  qDebug()<<"in receiveme";
     while(1){
          numbytes=recv(sockfd,receivebuf,sizeof(receivebuf),0);
        if(numbytes<0)
        {
            qDebug()<<"le bhai baj gaya band";
            qDebug()<<errno;
            break;
        }
        else if(numbytes==0)//connection closed
            return;
       receivebuf[1023]='\0';
       // qDebug()<<receivebuf;
        QString a=QString::fromLocal8Bit(receivebuf);
        QMetaObject::invokeMethod(this,"outputmessagereceived");
       //( outputbox)->append(a);
}
}
