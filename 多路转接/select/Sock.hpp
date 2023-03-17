#include<cstdlib>
#include<cstdio>
#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
class Sock
{
    public:
        static int Socket()
        {
            int sock=socket(AF_INET,SOCK_STREAM,0);
            if(sock<0)
            {
                std::cerr<<"socket error"<<std::endl;
                exit(1);
            }
            int opt=1;
            setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

        }
        static void Bind(int sock,uint16_t port)
        {
           struct sockaddr_in local;
           memset(&local,0,sizeof(local));
           local.sin_family=AF_INET;
            local.sin_port=htons(port);
            local.sin_addr.s_addr=INADDR_ANY;
            if(bind(sock,(struct sockaddr*)(&local),sizeof(local))<0)
            {
                std::cerr<<"bind error"<<std::endl;
                exit(2);
            }
        }
        static void Listen(int sock)
        {
            if(listen(sock,5)<0)
            {
                std::cerr<<"listen error"<<std::endl;
                exit(3);
            }
        }
        static int Accept(int sock)
        {
            struct sockaddr_in peer;
            socklen_t len=sizeof(peer);
            int fd=accept(sock,(struct sockaddr*)&peer,&len);
            if(fd>=0)
            {
               return fd;
            }
            return -1;
        }
        static void Connect(int sock,std::string ip,uint16_t port)
        {   
            struct sockaddr_in server;
            server.sin_addr.s_addr=inet_addr(ip.c_str());
            server.sin_port=htons(port);
            server.sin_family=AF_INET;
            if(connect(sock,(struct sockaddr*)&server,sizeof(server))==0)
            {
                std::cout<<"connect success"<<std::endl;
            }
            else
            {
                std::cout<<"connect fail"<<std::endl;
                exit(4);
            }
            
        }

};