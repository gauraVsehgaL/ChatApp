#ifndef SERV
#define SERV
#ifndef SERVER
#define SERVER
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<QWidget>
#include<QDebug>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<vector>
#include<QTextEdit>
class server:public QWidget
{
    Q_OBJECT
public:
    fd_set master;
    fd_set read_fds;
    char fakename[15];
    char fakename2[5];
    int fdmax;
    int listener;
    int newfd;
    QString temp;
    char* port;
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;
    QLabel *label,*newlable;
    QGridLayout *lay;
    QPushButton *stophosting;
    QTextEdit *connectednames;
    char buf[1000];
    int nbytes;
    struct avi
    {
        int fd;
        char name[15];
    };
    char remoteip[INET6_ADDRSTRLEN];
    int i,j,rv;
    struct addrinfo hints,*ai,*p;
    bool stop=false;
    char sendersinfo[2500];
    //std::pair<std::pair<char*,int>,char*> clientnamehai;
    std::vector<std::pair<std::pair<char*,int>,char*> > clientnamelist;
    std::vector<struct avi> clientnamelist2;
public:
    void* get_in_addr(struct sockaddr *sa);
    server();
    int ijk=1;
    void work();
    void setserverui();
    int basicwork();
    void add_cient_name(char* ip, int port, char *name);
    void add_cient_name2(int fd, char name[]);
    void remove_cient_name2(int fd);
    char* get_client_name(char* ip,int port);
    char* get_client_name2(int fd);
    Q_INVOKABLE void showclientnames();
public slots:
    void stopserver();
};
#endif // SERVER
#endif // SERV
