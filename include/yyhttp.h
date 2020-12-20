#ifndef __YYHTTP_H__
#define __YYHTTP_H__

#include "yysock.h"
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"

void accept_requests(int);
void cat(int, FILE*);
int get_line(int, char*, int);
void headers(int, const char*);
void not_found(int);
void serve_file(int, const char*);
void unimplemented(int);

#endif
