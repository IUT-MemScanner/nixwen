/*
* =====================================================================================
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
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/signal.h>
#include <sys/signal.h>

#include <algorithm>
#include <cctype>
#include <regex>

#include <list>
#include <map>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <stdexcept>

#include "maps.h"
#include "commands.h"

#include "langue.h"
#include "utils.hpp"


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


		// function for customize the default autocompletion
		rl_attempted_completion_function = commands_completion;

		// initialisation des variables de commande
		string c = "";
		char *line;

		cout << "Status de wait : " << status << endl;

		cout << "Stack : " << hex << getDebutStack(pid) << dec << endl;

		cout << "Child PID : " << pid << endl;
		// main loop


		Langue texte = Langue("fr","tui");
		cout << texte.welcome_msg() << endl;




		while((line = readline("> "))){
			c = string(line);
			if (c=="") {
				c = "0";
			}
			while(c.substr(c.size()-1, c.size()) == " "){ c.pop_back(); }

			vector<string> commandes = utils::explode(c, " ");


			// Ajoute les commandes a l'historique
			if(c != ""){
				add_history(line);
			}else{
				cout << texte.quick_help() << endl;
			}

			// Commande "exit"
			if( commandes[0]=="exit" ){
				break;
			}

			// Commande "cont"
			if(commandes[0] == "cont"){
				ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
				running = true;
			}

			// Commande "stop"
			if( commandes[0] == "stop" && running){
				// Caution ! If it happen twice, wait will be stuck !
				kill(pid, SIGSTOP);
				wait(&status);
				running = false;
			}

			// Commande "fuzzysearch"
			if( commandes[0] == "fuzzysearch" && !running){
				currentSize = dataSize;

				mapR = fuzzsearch(pid, mapR); // BORDER EFFECT !
				cout << mapR.size() << texte.fuzzysearch_msg() << endl;
				/* fill list (pointers) (first search)*/
			}

			// Commande "search"
			if( commandes[0] == "search" && !running){
				if (commandes.size() >= 2) {
					int choice;
					try{
						choice = stoi(commandes[1]);
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
							if (commandes.size() >= 3) {
								long value = stol(commandes[2]);
								mapR = fuzzsearch(choice, mapR, value, 0, pid);
							}
							else {
								cerr << texte.missing_argument("") << endl;
							}

							break;
							case 6:
							if (commandes.size() >= 4)  {
								long lbound, hbound;
								lbound = stoi(commandes[2]);
								hbound = stoi(commandes[3]);
								mapR = fuzzsearch(6, mapR, lbound, hbound, pid);
							}
							else {
								cerr << texte.missing_argument("search") << endl;
							}
							break;
							default:
							cout << texte.search_help() << endl;
						}
					}
					catch (const invalid_argument& ia) {
						std::cerr << texte.error_invalid_argument("search") << std::endl;
					}
					catch (const out_of_range& oor) {
						std::cerr << texte.error_out_of_range("an integer") << std::endl;
					}
				}
				else {
					cout <<  texte.search_help() << endl;
				}

			}


			// Commande "list", affiche les n valeurs trouver après recherche
			if( commandes[0] == "list"){

				int size = 10;
				if ((commandes.size() >= 2))
				{
					try{
						size = stoi(commandes[1]);
					}
					catch (const invalid_argument& ia) {
						// std::cerr << texte.error_invalid_argument("list") << std::endl;
					}
					catch (const out_of_range& oor) {
						std::cerr << texte.error_out_of_range("an integer") << std::endl;
					}
				}

				list_m(mapR, size, pid);


				/* display the `size` first found values that matched last research */
			}


			// Commande "alter"
			if( commandes[0] == "alter"){
				if (commandes.size() >= 3) {
					try{
						long n;
						long v;
						n = stol(commandes[1],NULL,16);

						if(mapR.end() != mapR.find((void*)n)){
							v = stol(commandes[2],NULL,10);

							if(v <= pow(2,currentSize)) { alter((void*)n, v, pid); }
							else{ cout << texte.alter_msg("boundary") << endl;}
						}else{
							cout << texte.alter_msg("not_found") << endl;
						}
					}
					catch (const invalid_argument& ia) {
						std::cerr << texte.error_invalid_argument("alter") << std::endl;
					}
					catch (const out_of_range& oor) {
						std::cerr << texte.error_out_of_range("a long") << std::endl;
					}
				}
				else {
					std::cout << texte.missing_argument("alter") << endl;
				}
			}

			if( commandes[0] == "fstart"){

				ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
				running = true;

				if (commandes.size() >= 2) {
					try{
						sleep(stoi(commandes[1]));
					}
					catch (const invalid_argument& ia) {
						std::cerr << texte.error_invalid_argument("fstart") << std::endl;
					}
				catch (const out_of_range& oor) {
					std::cerr << texte.error_out_of_range("an integer") << std::endl;
				}
			}
			else {
				sleep(2);
			}

			if(running){
				// Caution ! If it happen twice, wait will be stuck !
				kill(pid, SIGSTOP);
				wait(&status);
				running = false;
			}


		}
		// Commande "help"
		if( commandes[0] == "help"){
			cout << texte.quick_help() << endl;
		}


		commandes.clear();
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
