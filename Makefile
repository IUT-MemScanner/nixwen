CC=g++
DEBUG = -g
CFLAGS = -c -Wall  $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11
EXEC=main

all: $(EXEC) clean

main: main.o maps.o commands.o
	$(CC) $(LFLAGS) dbg.o maps.o -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

commands.o: commands.cpp
	$(CC) $(CFLGS) -o $@ $<

maps.o: maps.cpp
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -rf *.o

cleanAll: clean
	rm -rf dbg
