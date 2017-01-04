OBJ= maps.o
CC=g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG)
EXEC=dbg

all: $(EXEC)

dbg: dbg.cpp $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(CFLAGS)

maps.o: maps.h
	$(CC) -o $@ $< -c -g $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf dbg
