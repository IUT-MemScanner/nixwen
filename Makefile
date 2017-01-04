CC=g++
CFLAGS= -Wall -std=c++11
LDFLAGS=
EXEC=dbg

all: $(EXEC)

dbg: maps.o dbg.cpp
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.h
	$(CC) -o $@ -c $< -W $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf dbg
