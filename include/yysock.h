#ifndef __YYSOCK_H__
#define __YYSOCK_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>     //htons()
#include <bits/socket.h>    //sockaddr
#include <arpa/inet.h>      //ip地址格式转换
#include <sys/types.h>      //socket()
#include <sys/socket.h>     //socket()

int  create_sock(int);
void perror_exit(const char *);

#endif
