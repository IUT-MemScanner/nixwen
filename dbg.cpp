/*
 * =====================================================================================
 * http://www.secretmango.com/jimb/Whitepapers/ptrace/ptrace.html
 *       Filename:  dbg.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/12/2016 15:29:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/signal.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "maps.h"

using namespace std;

long getPos(long pid){
	struct user_regs_struct reg;
	
	ptrace(PTRACE_GETREGS, pid, NULL, &reg);

	#ifdef __x86_64__
		return reg.rip;
	#elif defined __i386__
		return reg.eip;
	#endif
}

long getEax(long pid){
	struct user_regs_struct reg;

	ptrace(PTRACE_GETREGS, pid, NULL, &reg);

	#ifdef __x86_64__
		return reg.rax;
	#elif defined __i386__
		return reg.eax;
	#endif
}

int main (int argc, char *argv[]) {
	int status = 0;
	char * prog = argv[1];
	char *emp[] = {NULL};

	long pid = fork();

	if(pid==0){
		int m = ptrace(PTRACE_TRACEME, 0, 0, 0);

		int descF = open("nohup", O_CREAT, S_IRWXU);
		if(descF == -1){ exit(255); }
		close(STDOUT_FILENO);
		dup2(descF, STDOUT_FILENO);
		execve(prog, emp, emp);

		kill(getppid(), 9); // If the child fail, kill his father
	}else{
		wait(&status);
	
		cout << "Status de wait : " << status << endl;

		cout << "Stack : " << hex << getDebutStack(pid) << endl;

		struct user_regs_struct regs;
		int i = -1;

		cout << "pid" << pid << endl;	
		// main loop
		while(1){
				cout << "Entrez : ";
				cin >> i;
				if(i== 0){ptrace(PTRACE_CONT, pid, NULL, SIGCONT);}
				else{ // Caution ! If it happen twice, wait will be stuck ! 
					kill(pid, SIGSTOP);
					wait(&status);
				 }

		}

		cout << "Father "<< getpid() <<" died, child was "<< pid << endl,
	}



	return 0;
}
