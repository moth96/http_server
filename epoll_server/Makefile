target = server

src = main.c ../include/yysock.c ../include/yyhttp.c
obj = main.o ../include/yysock.o ../include/yyhttp.o

CC = gcc

$(target):$(obj)
	$(CC) $(obj) -o $(target)

%.o:%.c
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	rm $(obj) $(target) -f


