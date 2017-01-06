#ifndef COMMANDS_H
#define COMMANDS_H

#include <list>
#include <map>
#include <stdbool.h>

// searcher
std::list<void *> search(long value, std::list<void *> l ,bool isnew, long pid);

// TODO : Fuzzy search
/* Fuzzy search
 *
 * @return the list of the found values
 */
// map<void *, long> fuzzsearch(long pid); // init
// map<void *, long> fuzzsearch(int opId, long changed, map<void *, long> map, long pid); // search

// list max values in the list
void list_v(std::list<void *> l, int max);

// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid);

#endif
