#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
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
// searcher
list<void *> search(long value, list<void *> list ,bool isnew, long pid){
	void * b = getDebutStack(pid);
	void * e = getFinStack(pid);
	void * p = b;
	if(isnew) list = {};

	while (p < e && isnew){
		if(value  == ptrace(PTRACE_PEEKDATA, pid, p, NULL))
			list.push_back(p);
	}
	if(!isnew){
			list.remove_if([&](void * o){return value != ptrace(PTRACE_PEEKDATA, pid, o, NULL); });
	}
		
	return list;
}

// TODO : Fuzzy search
/* Fuzzy search
 *
 * @return the list of the found values
 */
// map<void *, long> fuzzsearch(); // init
// map<void *, long> fuzzsearch(int opId, long changed, map<void *, long> map); // search

// list max values in the list
void list_v(list<void *> list, int max){
	for(int i = 0; i < max && i < list.size(); i++)
		cout << i << " : " << list[i] << endl;
}

// alter a value with a new value
bool alter(void* pointer, long newvalue){
	return true;
}

