CC=g++
CFLAGS= -Wall -std=c++11
LDFLAGS=
EXEC=dbg

all: $(EXEC)

dbg: maps.o dbg.cpp
	$(CC) -o $@ $^ $(CFLAGS)

maps.o: maps.h
	$(CC) -o $@ $< -W $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf dbg
