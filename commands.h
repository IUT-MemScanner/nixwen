/**
 * \file      commands.h
 * \version   2.0
 * \brief     Interface en ligne de commande pour nixwen
 */
#ifndef COMMANDS_H
#define COMMANDS_H

#include <list>
#include <map>
#include <stdbool.h>

std::map<void *, long> fuzzsearch(long pid, std::map<void *, long> memoire, int type); // init
std::map<void *, long> fuzzsearch(int codeOperation, std::map<void *, long> memoire, long value1, long value2, long pid, int type); // search

// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid, int type);
long get(void * pointer, int type, int pid);


#endif
