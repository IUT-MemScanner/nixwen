OBJ=
CC=g++
DEBUG = -g
CFLAGS = -c -Wall  $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11
EXEC=dbg

all: $(EXEC)

dbg: dbg.o maps.o
	$(CC) $(LFLAGS) dbg.o maps.o -o $@ 


dbg.o: dbg.cpp
	$(CC) $(CFLAGS) -o $@ $<

maps.o: maps.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o

mrproper: clean
	rm -rf dbg
