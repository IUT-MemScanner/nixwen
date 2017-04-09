CC=g++
DEBUG = -g
CFLAGS = -c -Wall  $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11
LIB = -lreadline
EXEC=nixwen

all: $(EXEC) clean

nixwen: nixwen.cpp maps.cpp commands.cpp utils.cpp langue.cpp tui.cpp
	$(CC) $(LFLAGS) $^ -o $@ $(LIB)


.PHONY: clean

clean:
	rm -rf *.o

cleanAll: clean
	rm -rf nixwen nohup
