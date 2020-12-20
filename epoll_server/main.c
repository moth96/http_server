#include "../include/yyhttp.h"
#include "../include/yysock.h"
#include <sys/epoll.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

// 将文件描述符设置成非阻塞的
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将文件描述符fd上的EPOLLIN注册到epollfd指示的epoll内核事件表中
//参数enable_et指定是否对fd启动ET模式
void addfd(int epollfd, int fd, int enable_et)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et)
    {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

//ET工作模式
void et(struct epoll_event* events, int number, int epollfd, int listenfd)
{
    //遍历事件集合
    for (int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        //新的连接
        if (sockfd == listenfd)
        {
            struct sockaddr_in client;
            socklen_t client_addr_len = sizeof(client);
            int connfd = accept(listenfd, (struct sockaddr*)&client, &client_addr_len);
            //将新连接加入监听事件
            addfd(epollfd, connfd, 1);
        }
        //对写事件处理
        else if(events[i].events & EPOLLIN)
        {
            //接受并处理http请求
            accept_requests(sockfd);
        }
    }
}

int main(int argc, char* argv[])
{
    //端口号 默认值9000 
    //可由参数列表给定
    int server_port = 9000;
    if (argc > 1)
    {
        server_port = atoi(argv[1]);
    }
    
    int listenfd = create_sock(server_port); 

    struct epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(10);
    if (epollfd < 0)
    {
        perror_exit("epoll_create error");
    }
    addfd( epollfd, listenfd, 1);
    while(1)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0)
        {
            perror_exit("epoll_wait error");
        }
        et(events, ret, epollfd, listenfd);
    }
    close(listenfd);

    return 0;
}

        
