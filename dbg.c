/*
 * =====================================================================================
 * http://www.secretmango.com/jimb/Whitepapers/ptrace/ptrace.html
 *       Filename:  dbg.c
 *
 *    Description:
i
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/signal.h>

#include "maps.h"

long getPos(long pid){
	struct user_regs_struct reg;

	kill(pid, SIGSTOP);
	ptrace(PTRACE_GETREGS, pid, NULL, &reg);

	#ifdef __x86_64__
		return reg.rip;
	#elif defined __i386__
		return reg.eip;
	#endif
}

long getEax(long pid){
	struct user_regs_struct reg;

	kill(pid, SIGSTOP);
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
		execve(prog, emp, emp);
		kill(getppid(), 9);
	}else{
		wait(NULL);

		printf("%x\n",getDebutStack(pid));

		struct user_regs_struct regs;
		int i = -1;

		// Assert that the program have been stoped
		kill(pid, SIGSTOP);

		long pos = getPos(pid);
		long last = -1;

		printf("%x", pos);

		// main loop
		while(1){
			kill(pid, SIGSTOP);

						while(last == pos){
							int res = ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
							if(res < 0 ){ printf("\nNooooo%d\n(repeat)\n", res); exit(0);}
							waitpid(0, &status, WSTOPPED);
							pos = getPos(pid);

							printf(" (r) %d ", pos);
						}

						// reset the last pos
						last = pos;

			// program bounds : TODO
			// Skip the outside
			while(pos < 0x400000 || pos > 0x602000){
				int res = ptrace(PTRACE_CONT, pid, NULL, NULL);
				if(res < 0 ){ printf("\nNooooo%d\n (oob)\n", res); exit(0);}
				waitpid(0, &status, WSTOPPED);
				pos = getPos(pid);
				printf(" (o) %d ", pos);
			// 5a 4a3 77d
			}


			printf("$ ");
			scanf("%d", &i);
			printf("pos : 0x%x\t eax : %d\n", getPos(pid), getEax(pid));
		}

		printf("Father %d died, child was %d\n",getpid(), pid);
	}



	return 0;
}
