/*
 * =====================================================================================
 * http://www.secretmango.com/jimb/Whitepapers/ptrace/ptrace.html
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.2
 *        Created:  06/12/2016 15:29:55
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

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
#include "commands.h"

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
string getHelp();

int main (int argc, char *argv[]) {
	int status = 0;
	char * prog = argv[1];
	char *emp[] = {NULL};

	long pid = fork();

	if(pid==0){
		int m = ptrace(PTRACE_TRACEME, 0, 0, 0);

		int descF = open("nohup", O_CREAT | O_TRUNC |O_WRONLY, S_IRWXU);
		if(descF == -1){ kill(getppid(), 9); exit(255); }
		cout << "Opened" << endl;
		close(STDOUT_FILENO);
		dup2(descF, STDOUT_FILENO);
		cout << "test" << endl;
		execve(prog, emp, emp);

		kill(getppid(), 9); // If the child fail, kill his father
	}else{
		wait(&status);
		bool running = false;

		int dataSize = 16;
		int currentSize = 16;
		list<void*> searchResult;
		map<void*, long> mapR;
		cout << "Status de wait : " << status << endl;

		cout << "Stack : " << hex << getDebutStack(pid) << dec << endl;

		struct user_regs_struct regs;
		int i = -1;

		cout << "Child PID : " << pid << endl;
		// main loop
		string c = "";
		while(c != "exit"){

				cout << "# ";
				cin >> c;
				if(c == "cont"){
					ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
					running = true;
				}
				if( c == "stop" && running){
				// Caution ! If it happen twice, wait will be stuck !
					kill(pid, SIGSTOP);
					wait(&status);
					running = false;
				}
				if( c == "fuzzysearch" && !running){
					currentSize = dataSize;

					mapR = fuzzsearch(pid, mapR); // BORDER EFFECT !
					cout << mapR.size() << " résultats trouvés." << endl;
			        /* fill list (pointers) (first search)*/
				}
				if( c == "fsearch" && !running){
					long value;
					cout << "Entrez une valeur : ";
					cin >> value;
					currentSize = dataSize;

//					search(value, searchResult, true, pid); // BORDER EFFECT !
//					cout << searchResult.size() << " résultats trouvés." << endl;
					mapR = fuzzsearch(0, mapR, value, NULL, pid);
			        /* fill list (pointers) (first search)*/
				}
				if( c == "fzsearch" && !running){
					long value;
					cout << "Entrez une valeur : ";
					cin >> value;

					searchResult = search(value, searchResult, false, pid);
					cout << searchResult.size() << " résultats trouvés." << endl;
					/* remove pointers of the list that point to value different */
					/* use currentSize */
				}
				if( c == "list"){
					int size;
					cout << "Entrez le nombre de valeurs souhaitée : ";
					cin >> size;

					/* display the `size` first found values that matched last research */
				}
				if( c == "size"){
					int v;
					cout << "Entrez une taille (1,2,4 ou 8) : ";
					cin >> v;
					if(v==8 || v==16 || v==32 || v==64){ dataSize = v; }
					/* Set the size of the searched data */
				}
				if( c == "alter"){
					int n;
					long v;
					cout << "Entrez la position : ";
					cin >> n;

					cout << "Entrez la valeur souhaitée : ";
					cin >> v;

					if(v <= pow(2,currentSize)) {/* do the alteration */}
					else{ cout << "La valeur est en dehors des bornes pour la taille actuelle" << endl;}
				}
				if( c == "help"){cout << getHelp() << endl;}
		}
		kill(pid, 9); // Be sure to kill the child mhouahahaha
		cout << "Father "<< getpid() <<" died, child was "<< pid << endl;
	}
	return 0;
}

string getHelp(){
	return "Commandes\n  cont -- reprendre l'exécution du programme\n  stop -- stoper l'exécution du programme\n  fsearch -- initialiser une recherche\n  fuzzysearch -- initialiser une recherche fuzzy\n  search -- continuer une recherche commencer avec fsearch ou fuzzysearch\n  list -- afficher les résultats de la recherche\n  size -- definir la taille des données à rechercher\n  alter -- modifier le contenu à une adresse choisie parmi ceux proposer parmi la commande list\n";
}
