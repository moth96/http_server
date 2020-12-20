target = server

src = main.c ../include/yysock.c ../include/yyhttp.c
obj = main.o ../include/yysock.o ../include/yyhttp.o

CC = gcc

CFLAGS = -std=c99

$(target):$(obj)
	$(CC) $(CFLAGS) $(obj) -o $(target)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm $(obj) $(target) -f


