CC=gcc
CFLAGS=-Wall -g

all: mainapp

mainapp: server.o
	$(CC) $(CFLAGS) server.o -o mainapp

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o mainapp
