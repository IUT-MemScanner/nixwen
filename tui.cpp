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

#include "nixwen.hpp"
#include "langue.h"
#include "utils.hpp"


// add -lreadline to compiler
#include  <readline/readline.h>
#include  <readline/history.h>

using namespace std;

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

    Nixwen nix = Nixwen(argc,argv,en);


		// function for customize the default autocompletion
		rl_attempted_completion_function = commands_completion;

		// initialisation des variables de commande
		string c = "";
		char *line;

		cout << "Child PID : " << nix.getPid() << endl;

    //initialisation of the text
		Langue texte = Langue("fr","tui");

		cout << texte.welcome_msg() << endl;

	   // main loop
		while((line = readline("> "))){
			c = string(line);

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
        if (-1 == nix.cont()) {
          std::cout << texte.getString("isrunning","running") << std::endl;
        }
			}

			// Commande "stop"
			if( commandes[0] == "stop"){
        if (-1 == nix.stop()) {
          std::cout << texte.getString("isstop","stopped") << std::endl;
        }
        nix.stop();
			}

			// Commande "fuzzysearch"
			if( commandes[0] == "fuzzysearch"){
        int ret = nix.init();
        if(-1 == nix.init()){
          std::cout << texte.getString("isrunning","running") << std::endl;
        }else{
          cout << ret << texte.fuzzysearch_msg() << endl;
        }

				/* fill list (pointers) (first search)*/
			}

			// Commande "search"
			if( commandes[0] == "search"){
				if (commandes.size() >= 2) {
					int choice;
					try{
						choice = stoi(commandes[1]);
						switch(choice){
							case 0:
							case 2:
							case 4:
							case 5:
                    nix.search(choice, 0, 0);
							break;
							case 1:
							case 3:
							case 7:
  							if (commandes.size() >= 3) {
  								long value = stol(commandes[2]);
                  nix.search(choice, value, 0);
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
                  nix.search(choice, lbound, hbound);
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
        map<void * , long> m = nix.list(size);
        int num = 0;
      	for(auto it = m.begin(); it != m.end(); ++it){
      		cout << num << " : (" << it->first << ") " <<  " ==> " << it->second  << endl;
      		num++;
      	}

				/* display the `size` first found values that matched last research */
			}


			// Commande "alter"
			if( commandes[0] == "alter"){
				if (commandes.size() >= 3) {
					try{
						long n;
						long v;
						n = stol(commandes[1],NULL,16);

						v = stol(commandes[2],NULL,10);

            nix.replace(n, v) ;

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
        int sleep;
				if (commandes.size() >= 2) {
					try{
						sleep = stoi(commandes[1]);
					}
					catch (const invalid_argument& ia) {
						std::cerr << texte.error_invalid_argument("fstart") << std::endl;
					}
				catch (const out_of_range& oor) {
					std::cerr << texte.error_out_of_range("an integer") << std::endl;
				}
			}
			else {
				sleep = 2;
			}
			nix.fstart(sleep);
		}
		// Commande "help"
		if( commandes[0] == "help"){
			cout << texte.quick_help() << endl;
		}

		commandes.clear();
		free(line);
		line = NULL;

	}

	nix.quit();
	cout << "Father "<< getpid() <<" died, child was "<< nix.getPid() << endl;
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
