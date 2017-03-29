/**
 * \file      commands.h
 * \version   2.0
 * \brief     Interface en ligne de commande pour nixwen
 */
#ifndef COMMANDS_H
#define COMMANDS_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>
#include <wait.h>

#include <list>
#include <map>
#include <math.h>

#include <fcntl.h>
#include <sys/stat.h>

#include "maps.h"

using namespace std;

std::map<void *, long> fuzzsearch(long pid, std::map<void *, long> memoire,
                                  int type); // init
std::map<void *, long> fuzzsearch(int codeOperation,
                                  std::map<void *, long> memoire, long value1,
                                  long value2, long pid, int type); // search
map<void *, char> stringSearch(string value, long pid);

// alter a value with a new value
bool alter(void *pointer, long newvalue, long pid, int type);
long get(void *pointer, int type, long pid);

#endif
