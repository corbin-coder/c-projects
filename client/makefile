CC=gcc
CFLAGS=-Wall -g

all: mainapp

mainapp: client.o
	$(CC) $(CFLAGS) client.o -o mainapp

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o mainapp
