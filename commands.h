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

std::map<void *, long> fuzzsearch(long pid, std::map<void *, long> m, int type); // init
std::map<void *, long> fuzzsearch(int opId, std::map<void *, long> m, long v1, long v2, long pid, int type); // search

// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid, int type);
long get(void * p, int type, int pid);


#endif
