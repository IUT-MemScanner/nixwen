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

// TODO : Fuzzy search
/* Fuzzy search
 *
 * @return the list of the found values
 */
map<void *, long> fuzzsearch(long pid, map<void *, long> m){ // init
	cout << "Starting search..." <<endl;

	void * b = getDebutStack(pid);
	void * e = getFinStack(pid);
	void * p = b;

	while (p < e){
		m[p] = ptrace(PTRACE_PEEKDATA, pid, p, NULL) & 0xFFFFFFFF;
		p = p + sizeof((int)(0));
	}

	p = getDebutHeap(pid);
	e = getFinHeap(pid);

	while (p < e){
		m[p] = ptrace(PTRACE_PEEKDATA, pid, p, NULL) & 0xFFFFFFFF;
		p = p + sizeof((int)(0));
	}

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
	for(auto it = m.begin(); it != m.end(); ++it){
		long n = ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF;
		switch(opId){
			case 0:
				if(it->second < n)
					newM[it->first] = n;
				break;
			case 1:
				if(it->second + v1 == n)
					newM[it->first] = n;
				break;
			case 2:
				if(it->second > n)
					newM[it->first] = n;
				break;
			case 3:
				if(it->second - v1 == n)
					newM[it->first] = n;
				break;
			case 4:
				if(it->second == n)
					newM[it->first] = n;
				break;
			case 5:
				if(it->second != n)
					newM[it->first] = n;
				break;
			case 6:
				if(n > v1 && n < v2)
					newM[it->first] = n;
				break;
            case 7:
                if(n == v1)
                  newM[it->first] = n;
                break;

            default:
				cout << "Error..." << endl;
		}
	}
	return newM;
}

void stringSearch(map<void *, long> m, long v1, long v2, long pid) {
	map<void *, long  > newM = {};
	for(auto it = m.begin(); it != m.end(); ++it){
		long n = ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF;
		newM[it->first] = n;

		}
}

// list max values in the list
void list_m(map<void *, long> m, int max, long pid){
	int num = 0;
    cout << "(pointeur) : valeur lors de la dernier recherche ==> valeur actuel"<< endl;
	for(auto it = m.begin(); it != m.end() && num < max; ++it){
		cout << num << " : (" << it->first << ") " << it->second  << " ==> " << (ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF) << endl;
		num++;
	}
}
// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid){
	return ptrace(PTRACE_POKEDATA, pid, pointer, newvalue) != -1;
}
