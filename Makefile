.POSIX:
CC     = cc
CFLAGS = -std=c99 -Wall -Wextra -O3 -g3

all: minimal_strace example example2

minimal_strace: minimal_strace.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ minimal_strace.c

example: example.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ example.c -lpthread

example2: example2.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ example2.c -lpthread

clean:
	rm -f minimal_strace example example2
