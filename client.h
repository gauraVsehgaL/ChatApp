#ifndef CLIENT
#define CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<QObject>
#include<QWidget>
#include<QTextEdit>
#include<QLineEdit>
#include<QDebug>
#include<QLabel>
#include<QPushButton>
#include<QtConcurrent/qtconcurrentrun.h>
#include<QThread>
#define PORT "3044" // the port client will be connecting to
#define MAXDATASIZE 1024 // max number of bytes we can get at once
class client:public QWidget//,public QThread
{
    Q_OBJECT
public:
    QThread thread;
  //  using QWidget::QObject;
    char *porti;//="3044";//the client to which we have to connect
       char *iptoconnect;//="127.0.0.1";//the client ip to which i want to connect
       //later get this as input
       int sockfd,numbytes;
      // char* buf;
       char buf[MAXDATASIZE];
       char receivebuf[MAXDATASIZE];
       struct addrinfo *iterator;
       int rv;
       struct addrinfo hints,*serviceinfo,*p;
       //int rv;
       char s[INET6_ADDRSTRLEN];
      // qDebug() <<"iamhere";
       char nickname[20];
       int temp;
       explicit client();
       void setclientui();
       void someshit();
       QTextEdit *outputbox;
       QLineEdit *inpbox;
       QString whatistobesent;
       QPushButton *avi;
       QPushButton *disconnect;

       //QLabel *outputbox;

void* get_in_addr(struct sockaddr *sa);
void sendclientname(char[]);
public slots:
int prework();
void sendme();
void disconnectchat();
void outputmessagereceived();
void receiveme();
/*
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
            close(sockfd);
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
    if(p==NULL)
    {
        //sad!!!!!
        fprintf(stderr,"client :failed to connect\n");
        return 2;
    }
    inet_ntop(iterator->ai_family,get_in_addr((struct sockaddr *)iterator->ai_addr),s,sizeof(s));
    printf("client: connecting to server %s\n:",s);
    freeaddrinfo(serviceinfo);//now free the list of addresses

    //we are connected and we can communicate with server
    if ((temp = send(sockfd, "You either die a hero or live long enough to see yourself become the villain",90,0)) == -1)
        {
        //qDebug()<<"9";
            perror("send");
            exit(1);
        }
      //  buf[numbytes] = '\0';
      //  printf("client: received '%s'\n",buf);
        //close(sockfd);
return 0;
}*/
};

/*
#ifndef CLIENT_H
#define CLIENT_H
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#include<cstring>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<stdio.h>
#include<unistd.h>
//#include<QObject>
#define MAXDATASIZE 100//maximum number of bytes we can get at once
class client// : public QObject
{
  // Q_OBJECT
    char port[5]="3044";//the client to which we have to connect
    char iptoconnect[15]="127.0.0.1";//the client ip to which i want to connect
    //later get this as input
    int sockfd,numbytes;
    char buf[MAXDATASIZE];
    char g[19]="hey gaurav";
    //strcpy(buf,g);
    struct addrinfo hints,*serviceinfo,*p;
    int rv;
    char s[INET6_ADDRSTRLEN];
  public:
    // get sockaddr,ipv4 or ipv6
    //int connectit(int sockfd,struct sockaddr* ai_addr,int ai_addrlen);
    void *get_in_addr(struct sockaddr *sa);
  //  void senddata(std::string s);
    //void sen();
//int connectme();
//client *obj;
//public slots:
    int prework();
};
#endif // CLIENT_H
*/
#endif // CLIENT
