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
map<void *, long> fuzzsearch(long pid, map<void *, long> memoire, int type){ // init

	void * b = getDebutStack(pid);
	void * e = getFinStack(pid);
	void * pointer = b;

	while (pointer < e){
        switch(type){
        case 1:
            memoire[pointer] = ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
            pointer = pointer + sizeof((long)(0));
            break;
        case 2:
            memoire[pointer]  = (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((int)(0));
            break;
        case 3:
            memoire[pointer] = (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((short)(0));
            break;
        case 4:
            memoire[pointer] = static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((char)(0));
            break;
        }
	}

	pointer = getDebutHeap(pid);
	e = getFinHeap(pid);

	while (pointer < e){
        switch(type){
        case 1:
            memoire[pointer] = ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
            pointer = pointer + sizeof((long)(0));
            break;
        case 2:
            memoire[pointer]  = (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((int)(0));
            break;
        case 3:
            memoire[pointer] = (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((short)(0));
            break;
        case 4:
            memoire[pointer] = static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
            pointer = pointer + sizeof((char)(0));
            break;
        }
	}
	return memoire;
}

map<void *, long> fuzzsearch(int codeOperation, map<void *, long> memoire, long value1, long value2, long pid,int type){ // search
// codeOperation codes
// 0 : +   the value is greater
// 1 : +?  the value is greater by
// 2 : -   the value is lower
// 3 : -?  the value is lower by
// 4 : =   the value is the same
// 5 : /=  the value has changed
// 6 : ><  in between comparison
	map<void *, long> newM = {};
    long n;
	for(auto it = memoire.begin(); it != memoire.end(); ++it){
        switch(type){
        case 1:
            n = ptrace(PTRACE_PEEKDATA, pid, it->first, NULL);
            break;
        case 2:
            n = (long)((int)ptrace(PTRACE_PEEKDATA, pid, it->first, NULL));
            break;
        case 3:
            n = (long)((short)ptrace(PTRACE_PEEKDATA, pid, it->first, NULL));
            break;
        case 4:
            n = static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, it->first, NULL));
            break;
        }
		switch(codeOperation){
			case 0:
				if(it->second < n)
					newM[it->first] = n;
				break;
			case 1:
				if(it->second + value1 == n)
					newM[it->first] = n;
				break;
			case 2:
				if(it->second > n)
					newM[it->first] = n;
				break;
			case 3:
				if(it->second - value1 == n)
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
				if(n > value1 && n < value2)
					newM[it->first] = n;
				break;
      case 7:
          if(n == value1)
            newM[it->first] = n;
          break;
    	default:
				break;
		}
	}
	return newM;
}


//TODO
void stringSearch(map<void *, long> memoire, long value1, long value2, long pid) {
	map<void *, long  > newM = {};
	for(auto it = memoire.begin(); it != memoire.end(); ++it){
		long n = ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF;
		newM[it->first] = n;
		}
}

long get(void * pointer, int type, int pid){
    /** id codes
    1 : long  (64b - 8o)
    2 : int   (32b - 4o)
    3 : short (16b - 2o)
    4 : char  (8b  - 1o)
**/
    switch(type){
        case 1:
            return ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
        case 2:
            return (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
        case 3:
            return (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
        case 4:
            return (long)((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
        default:
            return 0xDEADBEEF;
    }
}


// alter a value with a new value
bool alter(void* pointer, long newvalue, long pid, int type){
	/** id codes
    1 : long  (64b - 8o)
    2 : int   (32b - 4o)
    3 : short (16b - 2o)
    4 : char  (8b  - 1o)
	**/
	long curV = get(pointer, type,pid);
	switch(type){
        case 1:
            return ptrace(PTRACE_POKEDATA, pid, pointer, newvalue) != -1;
            break;
        case 2:
            return ptrace(PTRACE_POKEDATA, pid, pointer, (curV & (((1 << 32)-1) << 32)) + ((unsigned int  )newvalue)) != -1;
            break;
        case 3:
            return ptrace(PTRACE_POKEDATA, pid, pointer, (curV & (((1 << 48)-1) << 16)) + ((unsigned short)newvalue)) != -1;
            break;
        case 4:
            return ptrace(PTRACE_POKEDATA, pid, pointer, (curV & (((1 << 56)-1) << 16)) + ((unsigned char )newvalue)) != -1;
            break;
        default:
						return false;
            break;
    }
}
