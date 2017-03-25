/**
 * \file      commands.h
 * \version   2.0
 * \brief     Interface en ligne de commande pour nixwen
 */
#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/signal.h>

#include <list>
#include <map>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "maps.h"

using namespace std;

std::map<void *, long> fuzzsearch(long pid, std::map<void *, long> memoire, int type); // init
std::map<void *, long> fuzzsearch(int codeOperation, std::map<void *, long> memoire, long value1, long value2, long pid, int type); // search

// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid, int type);
long get(void * pointer, int type, long pid);


#endif
