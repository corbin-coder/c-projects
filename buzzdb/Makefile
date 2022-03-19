CC=gcc
CFLAGS=-Wall -g

all: buzzdb

buzzdb: uuid.o hashtable.o
	$(CC) $(CFLAGS) uuid.o hashtable.o -luuid -o buzzdb

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o buzzdb
