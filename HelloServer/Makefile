
CC = gcc
CCFLAG = -Wall -Wextra -Werror -Wpedantic -std=c99 -g

all :
	$(CC) $(CCFLAG) -o server server.c
	$(CC) $(CCFLAG) -o client client.c

clean :
	rm -f server client
	rm -rf *.dSYM

re : clean all

PHONY : all clean re