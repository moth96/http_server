#include "yysock.h"

//返回创建的socket文件描述符
//传入参数 server_port -- 服务器端口号
int create_sock(int server_port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror_exit("socket error");
    }
    //创建IPv4 socket地址
    struct sockaddr_in address;
    //初始化为0
    bzero( &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(server_port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    if(ret < 0)
    {
        perror_exit("bind error");
    }

    ret = listen(sock, 5);
    if(ret < 0)
    {
        perror_exit("listen error");
    }

    return sock;
}

//判断错误并退出程序
void perror_exit(const char *s)
{
    perror(s);
    exit(1);
}
