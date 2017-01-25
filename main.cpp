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

#include <algorithm>
#include <cctype>
#include <regex>

#include <list>
#include <map>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>

#include "maps.h"
#include "commands.h"


// add -lreadline to compiler
#include  <readline/readline.h>
#include  <readline/history.h>

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
/* Prototype */
char **commands_completion(const char *, int, int);
char *commands_generator(const char *, int);

// List des valeur que peu prendre l'auto complétion'
char *commands[] = {
	(char *)"cont",
	(char *)"stop",
	(char *)"exit",
	//   (char *)"fsearch",
	(char *)"fuzzysearch",
	(char *)"search",
	//   (char *)"size",
	(char *)"alter",
	(char *)"list",
	(char *)"help",
	(char *)"fstart",
	NULL
};


int main (int argc, char *argv[],char* en[]) {
	int status = 0;
	char * prog = argv[1];
	char *emp[] = {NULL};

	long pid = fork();

	if(pid==0){
		int m = ptrace(PTRACE_TRACEME, 0, 0, 0);
		int descF = open("nohup", O_CREAT | O_TRUNC |O_WRONLY, S_IRWXU);
		if(m == -1 || descF == -1){ kill(getppid(), 9); exit(255); }
		close(STDOUT_FILENO);
		dup2(descF, STDOUT_FILENO);
		execve(prog, emp, en);

		kill(getppid(), 9); // If the child fail, kill his father
	}else{
		wait(&status);
		bool running = false;

		int dataSize = 16;
		int currentSize = 16;
		list<void*> searchResult;
		map<void*, long> mapR;

		bool mode = 0; // 0 : normal / 1 : fuzzy

		// function for customize the default autocompletion
		rl_attempted_completion_function = commands_completion;

		// initialisation des variables de commande
		string c = "";
		char *line;

		cout << "Status de wait : " << status << endl;

		cout << "Stack : " << hex << getDebutStack(pid) << dec << endl;

		cout << "Child PID : " << pid << endl;
		// main loop

		while((line = readline("> "))){
			c = string(line);

			while(c.substr(c.size()-1, c.size()) == " "){ c.pop_back(); }

			// Ajoute les commandes a l'historique
			if(c != ""){
				add_history(line);
			}

			// Commande "exit"
			if( c=="exit" ){
				break;
			}

			// Commande "cont"
			if(c == "cont"){
				ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
				running = true;
			}

			// Commande "stop"
			if( c == "stop" && running){
				// Caution ! If it happen twice, wait will be stuck !
				kill(pid, SIGSTOP);
				wait(&status);
				running = false;
			}

			// Commande "fuzzysearch"
			if( c == "fuzzysearch" && !running){
				currentSize = dataSize;
				mode = true; // Set to fuzzy

				mapR = fuzzsearch(pid, mapR); // BORDER EFFECT !
				cout << mapR.size() << " résultats trouvés." << endl;
				/* fill list (pointers) (first search)*/
			}

			// Commande "search"
			if( c == "search" && !running){
				if(mode){

					int choice;
					cout <<  "0 : +   the value is greater" << endl <<
					"1 : +?  the value is greater by"<< endl <<
					"2 : -   the value is lower"<< endl <<
					"3 : -?  the value is lower by"<< endl <<
					"4 : =   the value is the same"<< endl <<
					"5 : /=  the value has changed"<< endl <<
					"6 : ><  in between comparison"<< endl <<
					"7 : =? is the value"<< endl;

					cout << "Choix du mode : ";
					cin >> choice;

					switch(choice){
						case 0:
						case 2:
						case 4:
						case 5:
						mapR = fuzzsearch(choice, mapR, 0, 0, pid);
						break;
						case 1:
						case 3:
						case 7:
						long value;
						if (choice==7){
							cout << "Entrez une valeur recherchée : ";
						}else{
							cout << "Entrez une valeur de changement : ";
						}
						cin >> value;
						mapR = fuzzsearch(choice, mapR, value, 0, pid);
						break;
						case 6:
						long lbound, hbound;
						cout << "Entrez la valeur min : ";
						cin >> lbound;
						cout << "Entrez la valeur max : ";
						cin >> hbound;
						mapR = fuzzsearch(6, mapR, lbound, hbound, pid);
						break;
						default:
						cout << "Not implemented yet";
					}

				}else{
					int value;
					cout << "Entrez la valeur : ";
					cin >> value;

					search(pid, value, searchResult, false);
				}
			}

			// Commande "fsearch"
			// weird issue now this functionnalitie is implements in fuzzsearch
			// if( c == "fsearch" && !running){
			// 	mode = false; // Set to normal mode
			// 	long value;
			// 	cout << "Entrez une valeur : ";
			// 	cin >> value;
			// 	searchResult = search(pid ,value, searchResult, true);
			//             cout << searchResult.size() << " résultats trouvés." << endl;
			// 	/* remove pointers of the list that point to value different */
			// 	/* use currentSize */
			// }

			// Commande "list", affiche les n valeurs trouver après recherche
			if( c == "list"){

				int size;
				cout << "Entrez le nombre de valeurs souhaitée : ";
				cin >> size;

				if(mode){ list_m(mapR, size, pid);
				}else{ list_v(searchResult, size);
				}

				/* display the `size` first found values that matched last research */
			}

			// NOT IMPLEMENT
			// if( c == "size"){
			// 	int v;
			// 	cout << "Entrez une taille (1,2,4 ou 8) : ";
			// 	cin >> v;
			// 	if(v==8 || v==16 || v==32 || v==64){ dataSize = v; }
			// 	/* Set the size of the searched data */
			// }

			// Commande "alter"
			if( c == "alter"){

				long n;
				long v;
				cout << "Entrez le pointeur : ";
				cin >> hex >> n;

				if(mapR.end() != mapR.find((void*)n)){
					cout << "Entrez la valeur souhaitée : ";
					cin >> dec >> v;

					if(v <= pow(2,currentSize)) { alter((void*)n, v, pid); }
					else{ cout << "La valeur est en dehors des bornes pour la taille actuelle" << endl;}
				}else{
					cout << "Erreur, le pointeur n'est pas dans la liste" << endl;
				}
			}
			if( c == "fstart"){

				ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
				running = true;

				sleep(1);

				if(running){
					// Caution ! If it happen twice, wait will be stuck !
					kill(pid, SIGSTOP);
					wait(&status);
					running = false;
				}


			}
			// Commande "help"
			if( c == "help"){
				cout << "Commandes:\n"
				"  exit -- Quitter le programme"
				"  cont -- reprendre l'exécution du programme\n"
				"  stop -- stoper l'exécution du programme\n"
				"  fuzzysearch -- initialiser une recherche fuzzy\n"
				"  search -- continuer une recherche commencer avec fsearch ou fuzzysearch\n"
				"  list -- afficher les résultats de la recherche\n"
				"  fstart -- reprendre l'exécution du programme puis le re stoper\n"
				"  alter -- modifier le contenu à une adresse choisie parmi ceux proposer parmi la commande list\n"
				"  help -- Afficher les commandes disponibles"  << endl;
			}

			free(line);
			line = NULL;
		}
		kill(pid, 9); // Be sure to kill the child mhouahahaha
		cout << "Father "<< getpid() <<" died, child was "<< pid << endl;
	}
	return 0;
}

char **commands_completion(const char *text, int start, int end)
{
	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, commands_generator);
}

char *commands_generator(const char *text, int state)
{
	static int list_index, len;
	char *name;

	if (!state) {
		list_index = 0;
		len = strlen(text);
	}

	while ((name = commands[list_index++])) {
		if (strncmp(name, text, len) == 0) {
			return strdup(name);
		}
	}

	return NULL;
}
