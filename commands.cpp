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
	void * bb = getDebutHeap(pid);
	void * ee = getFinHeap(pid);
	void * p = b;
	int m = 0; // 0 : stack search / 1 : heap search
	if(isnew) list = {};

	while (((p < e && m==0) || (p < ee && m==1)) && isnew){
		if(m==0){
			cout << "\r" << p << "/ "<< e;
			if(value  == ptrace(PTRACE_PEEKDATA, pid, p, NULL))
				list.push_back(p);
			p = p + sizeof((int)(0));
			if(p>=e){
				m = 1;
				p = bb;
			}
		}else{
			cout << "\r" << p << "/ "<< ee;
			if(value  == ptrace(PTRACE_PEEKDATA, pid, p, NULL))
				list.push_back(p);
			p = p + sizeof((int)(0));	
		}
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
			default:
				cout << "Error..." << endl;
		}
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

