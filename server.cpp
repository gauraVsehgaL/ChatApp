#include "server.h"
void server::setserverui()
{
 label=new QLabel("hosting a chat at some port");
 lay=new QGridLayout;
 lay->addWidget(label,0,0);
 stophosting=new QPushButton;
 stophosting->setText("stop hosting!");
 lay->addWidget(stophosting,1,0);
 setLayout(lay);
 connectednames=new QTextEdit;
 connectednames->setReadOnly(true);
 lay->addWidget(connectednames,0,1);
 QObject::connect(stophosting,SIGNAL(clicked()),this,SLOT(stopserver()));
}
void server::showclientnames()
{
    //first clear it
    connectednames->clear();
    for(std::vector<struct avi>::iterator it=clientnamelist2.begin();it!=clientnamelist2.end();it++)
    {
        struct avi newavi=*it;
        connectednames->append(newavi.name);
    }
}
void server::stopserver()
{
    qDebug()<<"band";
    stop=true;
    newlable=new QLabel("hosting stopped at some port");
    QGridLayout *newlay=new QGridLayout;
    newlay->addWidget(newlable);
  //  lay->replaceWidget(label,newlable);
    //lay->removeWidget(label);
    label->deleteLater();
    stophosting->deleteLater();
    lay->addWidget(newlable,0,0);
  //  lay->removeWidget(stophosting);
  //  lay->addWidget(newlable,0,0);
    //stophosting->setFocus();
   // lay->replaceWidget(label,newlable);
    //setLayout(newlay);
}
void server::add_cient_name2(int fd, char name[])
{
 //   clientname anotherone;
   // anotherone.second=23;
   // clientnamelist.push_back(anotherone);
    struct avi obj;
    obj.fd=fd;
    strcpy(obj.name,"\0");
    strcpy(obj.name,name);
   // anotherone=std::make_pair(name,fd);
    clientnamelist2.push_back(obj);
}
void server::remove_cient_name2(int fd)
{
    for(std::vector<struct avi>::iterator it=clientnamelist2.begin();it!=clientnamelist2.end();it++)
    {
        struct avi newavi=*it;
        if(newavi.fd==fd)
        {
            //delete this
            clientnamelist2.erase(it);
            break;
        }
    }
}
void server::add_cient_name(char *ip, int port, char *name)
{
 //   clientname anotherone;
   // anotherone.second=23;
   // clientnamelist.push_back(anotherone);
 //   std::pair<std::pair<char*,int>,char* > anotherone;
 //   anotherone=std::make_pair(std::make_pair(port,ip),name);
 //   clientnamelist.push_back(anotherone);
}
char* server::get_client_name2(int fd)
{
    for(std::vector<struct avi >::iterator it=clientnamelist2.begin();it!=clientnamelist2.end();it++)
    {
        struct avi anotherone;
        anotherone=*it;
        if(anotherone.fd==fd)
            return anotherone.name;
    }
}
char* server::get_client_name(char* ip,int port)
{
    for(std::vector<std::pair<std::pair<char*,int>,char*> >::iterator it=clientnamelist.begin();it!=clientnamelist.end();it++)
    {
        std::pair<std::pair<char*,int>,char*> anotherone;
        anotherone=*it;
        if(anotherone.first.first==ip && anotherone.first.second==port)
            return anotherone.second;
    }
}
server::server()
{
    FD_ZERO(&master);    // clear the master and temp sets
        FD_ZERO(&read_fds);
        // get us a socket and bind it
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        setserverui();




       // port[4]='\0';
       // qDebug()<<QString::fromLocal8Bit(port);

}
int server::basicwork()
{
    port=temp.toLocal8Bit().data();
    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
       exit(1);
    }
    for(p=ai;p!=NULL;p=p->ai_next)
    {
        listener=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if(listener<0)
        {
         continue;
        }
        if(bind(listener,p->ai_addr,p->ai_addrlen)<0)
        {
            ::close(listener);
            continue;
        }
        break;
    }
    if(p==NULL)
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }
    freeaddrinfo(ai);
    if(listen(listener,10)==-1)
    {
        perror("listen");
        exit(3);
    }
    FD_SET(listener,&master);
    fdmax=listener;
    return 1;//eveything well
}
void server::work()
{
    struct timeval tv;
    tv.tv_sec=1;
    tv.tv_usec=0;
/*   // port[4]='\0';
   // qDebug()<<QString::fromLocal8Bit(port);
    port=temp.toLocal8Bit().data();
    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
       exit(1);
    }
    for(p=ai;p!=NULL;p=p->ai_next)
    {
        listener=socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if(listener<0)
        {
         continue;
        }
        if(bind(listener,p->ai_addr,p->ai_addrlen)<0)

        {
            ::close(listener);
            continue;
        }
        break;
    }
    if(p==NULL)
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }
    freeaddrinfo(ai);
    if(listen(listener,10)==-1)
    {
        perror("listen");
        exit(3);
    }
    FD_SET(listener,&master);
    fdmax=listener;
   */ for(;;)
    {
        if(stop==true)
        {
            shutdown(listener,1);
            ::close(listener);
            //close all clients
            for(int i=0;i<=fdmax;i++)
             {
                if(FD_ISSET(i,&master))
                ::close(i);
            }
            break;
        }
        read_fds=master;
        if(select(fdmax+1,&read_fds,NULL,NULL,&tv)==-1)
        {
            perror("Select");
            exit(4);
        }
        for(i=0;i<=fdmax;i++)
        {
        //    if(stop==true)return;
            if(FD_ISSET(i,&read_fds))
            {
                if(i==listener)//ie a new connection
                {
                    addrlen=sizeof(remoteaddr);
                    newfd=accept(listener,(struct sockaddr*)&remoteaddr,&addrlen);
                    if(newfd==-1)
                    {
                        perror("accept");
                    }
                    else
                    {
                     //   FD_SET(newfd,&master);
                        if(newfd>fdmax)
                            fdmax=newfd;
                        //new connnection from
                      FD_SET(newfd,&master);
                        printf("selectserver: new connection from %s on "
                        "socket %d\n",

                               inet_ntop(remoteaddr.ss_family,
                        get_in_addr((struct sockaddr*)&remoteaddr),remoteip, INET6_ADDRSTRLEN),newfd);
              //          strcpy(sendersinfo,inet_ntop(remoteaddr.ss_family,
                //                                     get_in_addr((struct sockaddr*)&remoteaddr),
                  //                                   remoteip, INET6_ADDRSTRLEN));



                       // char fakename[5];//="iam:";//receive this shit
                       // char fakename2[5];
                       // char fakename3[5];

                         if(recv(newfd,fakename,sizeof(fakename),0)<=0)
                         {
                             qDebug()<<"naya navela";
                         }
                         else
                         {

                             socklen_t len;
                             struct sockaddr_storage addr;
                             char ipstr[INET6_ADDRSTRLEN];
                             int portis;
                             len = sizeof addr;
                             getpeername(newfd, (struct sockaddr*)&addr, &len);

                             // deal with both IPv4 and IPv6:
                             if (addr.ss_family == AF_INET) {
                                 struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                                 portis = ntohs(s->sin_port);
                                 inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
                             } else { // AF_INET6
                                 struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
                                 portis = ntohs(s->sin6_port);
                                 inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
                             }
                             qDebug()<<&fakename<<" "<<&fakename2<<" ";
                       //      strcpy(fakename2,fakename);
                            // add_cient_name(ipstr,portis,fakename);
                             add_cient_name2(newfd,fakename);
                           //  fakename[0]='\0';
                             //new client here so update the connectednames
                             QMetaObject::invokeMethod(this,"showclientnames");
                             strcpy(fakename,"\0");


                             //delete this
                             char aviavi[50];
                             gethostname(aviavi,sizeof(aviavi));
                             qDebug()<<aviavi;












                             //delete this



                         }
                      }
                }
                else
                {
                    //handle data from client
                    if((nbytes=recv(i,buf,sizeof(buf),0))<=0)
                    {
                            //error or connection closed
                        if(nbytes==0)
                        {
                            //connection closed
                            //client disconnected
                            remove_cient_name2(i);
                            //disconnected client name removed
                            //now update connectednames
                            QMetaObject::invokeMethod(this,"showclientnames");
                        }
                        else
                            perror("recv");
                        ::close(i);//in both cases connection has to be closed
                        FD_CLR(i,&master);
                  }
                    else
                    {
                        socklen_t len;
                        struct sockaddr_storage addr;
                        char ipstr[INET6_ADDRSTRLEN];
                        int portis;

                        len = sizeof addr;
                        getpeername(i, (struct sockaddr*)&addr, &len);

                        // deal with both IPv4 and IPv6:
                        if (addr.ss_family == AF_INET) {
                            struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                            portis = ntohs(s->sin_port);
                            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
                        } else { // AF_INET6
                            struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
                            portis = ntohs(s->sin6_port);
                            inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
                        }
                        char temp[15];
                        char yo[2];
                        yo[0]=':';
                        yo[1]=' ';
                        strcpy(temp,get_client_name2(i));
                        strcpy(sendersinfo, temp);
                        // strcat(sendersinfo,s->sin_port);
                        strcat(sendersinfo,yo);
                        strcat(sendersinfo,buf);
                        for(j=0;j<=fdmax;j++)
                        {
                            //send to everyone
                            if(FD_ISSET(j,&master))
                            {
                                if(j!=listener)
                                {
                                    if(send(j,sendersinfo,nbytes+strlen(yo)+strlen(temp),0)==-1)
                                    {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void* server::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);

}
