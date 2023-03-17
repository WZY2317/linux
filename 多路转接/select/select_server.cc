#include<sys/select.h>
#include<iostream>
#include"Sock.hpp"
static void Usage(char argv[])
{
     std::cout<<"usage ::" <<argv<< "port"<<std::endl;
}
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
       Usage(argv[0]);
       exit(1);
    }
    uint16_t port=(uint16_t)atoi(argv[1]);
    int listen_sock=Sock::Socket();
    Sock::Listen(listen_sock);
    Sock::Bind(listen_sock,port);
    fd_set rfds;
    for(;;)
    {
        FD_ZERO(&rfds);
        FD_SET(listen_sock,&rfds);
        int n=select(listen_sock+1,&rfds,nullptr,nullptr,nullptr);
        switch(n)
        {
            case -1:
                std::cerr<<"select error"<<std::endl;
            case 0:
                std::cout<<"time out"<<std::endl;
            default:
                std::cout<<"有对应的时间就绪了"<<std::endl;
            
        }
    }
    return 0;
}