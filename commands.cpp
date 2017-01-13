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
void search(long value, list<void *> list ,bool isnew, long pid){
	void * b = getDebutStack(pid);
	void * e = getFinStack(pid);
	void * p = b;
	if(isnew) list = {};

	while (p < e && isnew){
		cout << "\r" << p << "/ "<< e;
		if(value  == ptrace(PTRACE_PEEKDATA, pid, p, NULL))
			list.push_back(p);
		p = p + sizeof((int)(0));
	}
	if(!isnew){
			list.remove_if([&](void * o){return value != ptrace(PTRACE_PEEKDATA, pid, o, NULL); });
	}

	cout << list.size() << endl;
}

// TODO : Fuzzy search
/* Fuzzy search
 *
 * @return the list of the found values
 */
map<void *, long> fuzzsearch(long pid, map<void *, long> m){ // init
	cout << "zefr" <<endl;
	
	void * b = getDebutStack(pid);
	void * e = getFinStack(pid);
	void * p = b;

	while (p < e){
		m[p] = ptrace(PTRACE_PEEKDATA, pid, p, NULL);
		p = p + sizeof((int)(0));
	}
	cout << m.size() << " S " << endl;	
	return m;
}

map<void *, long> fuzzsearch(int opId, map<void *, long> m, long v1, long v2, long pid){ // search	
// opId codes
// 0 : +   the value is greater
// 1 : +?  the value is greater by
// 2 : -   the value is lower
// 3 : -?  the value is lower by
// 4 : =   the value is the same
// 5 : /=  the value has changed
// 6 : ><  in between comparison
	map<void *, long> newM = {};
	switch(opId){
		case 0: 
			for(auto it = m.begin(); it != m.end(); ++it){
				// cout << "ll " << it->first << endl;
				long n = ptrace(PTRACE_PEEKDATA, pid, it->first, NULL);
				if(it->second < n){ 
					cout << "keep " << it->first << " was " << it->second << " is " << n << endl; 
					newM[it->first] = n; 
				} 
			}
			break;
		default:
			cout << "not implemented yet" << endl;
	
	}
	
	return newM;

}


// list max values in the list
void list_v(list<void *> list, int max){
  auto it = list.begin();
  for(int i = 0; i < max && i < list.size(); i++){
		cout << i << " : " << *it << endl;
    ++it;
  }
}
// list max values in the list
void list_m(map<void *, long> m, int max, long pid){
	for(auto it = m.begin(); it != m.end(); ++it){
		cout << it->first << " : " << it->second  << " new " << ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) << endl;
	} 
}
// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid){
	return ptrace(PTRACE_POKEDATA, pid, pointer, newvalue) != -1;
}

