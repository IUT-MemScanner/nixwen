CC=g++
DEBUG = -g
CFLAGS = -c -Wall  $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11
LIB = -lreadline
EXEC=nixwen

all: $(EXEC) clean

nixwen: main.o maps.o commands.o utils.cpp langue.cpp
	$(CC) $(LFLAGS) $^ -o $@ $(LIB)

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

commands.o: commands.cpp
	$(CC) $(CFLAGS) -o $@ $<

maps.o: maps.cpp
	$(CC) $(CFLAGS) -o $@ $<



.PHONY: clean

clean:
	rm -rf *.o

cleanAll: clean
	rm -rf dbg
