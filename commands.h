#ifndef COMMANDS_H
#define COMMANDS_H

#include <list>
#include <map>
#include <stdbool.h>

// searcher
void search(long value, std::list<void *> l ,bool isnew, long pid);

// TODO : Fuzzy search
/* Fuzzy search
 *
 * @return the list of the found values
 */
std::map<void *, long> fuzzsearch(long pid, std::map<void *, long> m); // init
std::map<void *, long> fuzzsearch(int opId, std::map<void *, long> m, long v1, long v2, long pid); // search

// list max values in the list
void list_v(std::list<void *> l, int max);

// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid);

#endif
