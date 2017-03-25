CC=g++
DEBUG = -g
CFLAGS = -c -Wall  $(DEBUG) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11
LIB = -lreadline
EXEC=nixwen_tui

all: $(EXEC) clean

nixwen_tui: nixwen.cpp maps.cpp commands.cpp utils.cpp langue.cpp tui.cpp
	$(CC) $(LFLAGS) $^ -o $@ $(LIB)


.PHONY: clean

clean:
	rm -rf *.o

cleanAll: clean
	rm -rf nixwen nixwen_tui nohup
