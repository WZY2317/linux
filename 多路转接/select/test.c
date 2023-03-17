#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<fcntl.h>
#include<errno.h>
void GetNonBlock(int fd)
{
    int f1=fcntl(fd,F_GETFD);
    if(f1<0)
    {
        perror("error");
        return ;
    }
    fcntl(fd,F_SETFL,f1|O_NONBLOCK);
}
int main()
{
    GetNonBlock(0);
    while (1)
    {
        char buffer[1024];
        ssize_t s = read(0, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s] = 0;
            write(1, buffer, strlen(buffer));
            printf("%dsucess\n",s);
        }
        else
        {
            printf("faile errno:%d\n",errno);
        }
        sleep(1);
    }
    return 0;
}