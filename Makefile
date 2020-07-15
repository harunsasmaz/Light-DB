CC=gcc
CCFLAGS=-O3 -Wall
OBJECT=lightdb
SRC=$(wildcard *.c)

all: $(SRC)
	$(CC) $(CCFLAGS) -o $(OBJECT) $^

clean:
	rm -f lightdb

cleandb:
	rm -f *.db