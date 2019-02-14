.POSIX:
CC     = cc
CFLAGS = -std=c99 -Wall -Wextra -O3 -g3

#all: minimal_strace xpledge example
all: minimal_strace example

minimal_strace: minimal_strace.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ minimal_strace.c

#xpledge: xpledge.c
#	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ xpledge.c
#
example: example.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ example.c -lpthread

clean:
	rm -f minimal_strace xpledge example
