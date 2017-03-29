/**
* \file      tui.cpp
* \version   2.0
* \brief     Interface en ligne de commande pour nixwen
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ostream>
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
#include <string>
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
string customLine(int);
char **commands_completion(const char *, int, int);
char *commands_generator(const char *, int);

// List des valeur que peu prendre l'auto complétion'
char *commands[] = {
  (char *)"cont", // continuer
  (char *)"stop", // stopper
  (char *)"exit", //sortir
  (char *)"fuzzysearch", //initialisation recherche
  (char *)"search", //chercher
  (char *)"alter", //modifier
  (char *)"list",  //afficher
  (char *)"help",  //aide
  (char *)"fstart", //demarage arrêt auto après une durrée
  (char *)"type",  // definir le type de la prochaine recherche (setter)
  (char *)"gtype",  // récupérer le type (getter)
  (char *)"store",
  (char *)"list_store",
  (char *)"force_type",
  (char *)"stringSearch",
  NULL
};

int main (int argc, char *argv[],char* en[]) {

  Nixwen nix = Nixwen(argc,argv,en);


  // function for customize the default autocompletion
  rl_attempted_completion_function = commands_completion;

  // initialisation des variables de commande
  string c = "";
  char *line;

  char a = 'a';
  std::cout << sizeof(a) << '\n';
  cout << "Child PID : " << nix.getPid() << endl;

  //initialisation of the text
  Langue texte = Langue("fr","tui");
  cout << texte.welcome_msg() << endl;

  // main loop
  while((line = readline(customLine(nix.getType()).c_str()))){

    c = string(line);
    vector<string> commandes = utils::explode(c, " ");

    // Ajoute les commandes a l'historique
    if(c != ""){
      add_history(line);
    }else{
      cout << texte.quick_help() << endl;
    }


    //! Commande "exit"
    if( commandes[0]=="exit" ){
      break;
    }

    //! Commande "cont"
    else if(commandes[0] == "cont"){
      if (-1 == nix.cont()) {
        std::cout << texte.getString("isrunning","running") << std::endl;
      }
    }

    //! Commande "stop"
    else if( commandes[0] == "stop"){
      if (-1 == nix.stop()) {
        std::cout << texte.getString("isstop","stopped") << std::endl;
      }
      nix.stop();
    }

    //! Commande "fuzzysearch"
    else if( commandes[0] == "fuzzysearch"){
      int resultat = nix.init();
      if(resultat == -1){
        std::cout << texte.getString("isrunning","running") << std::endl;
      }else{
        std::cout << to_string(resultat) << texte.getString("fuzzysearch_msg", "") << endl;
      }
    }

    //! commande "type"
    else if(commandes[0] == "type"){
      if(commandes.size() >= 2){
        string c = commandes[1];
        int type = -1;
        if("long"==c){ type = 1;
        }else if("int"==c){ type = 2;
        }else if("short"==c){ type = 3;
        }else if("char"==c){ type = 4;
        }else{
          cout << texte.getString("wrongType","parrametre invalide") << endl;
        }
        if(nix.setType(type)==-1){
          cout << texte.getString("wrongType","parrametre invalide") << endl;
        }else{
          cout << texte.getString("setType","Set type : ") << c << '\n' <<texte.getString("activateType","") << endl;
        }
      }else{
        cout << texte.getString("typeHelp","invalide syntax") << endl;
      }
    }

    //! commande "force_type"
    else if(commandes[0] == "force_type"){
      if(commandes.size() >= 2){
        string c = commandes[1];
        int type = -1;
        if("long"==c){ type = 1;
        }else if("int"==c){ type = 2;
        }else if("short"==c){ type = 3;
        }else if("char"==c){ type = 4;
        }else{
          cout << texte.getString("wrongType","parrametre invalide") << endl;
        }
        if(nix.setCurrentType(type)==-1){
          cout << texte.getString("wrongType","parrametre invalide") << endl;
        }else{
          cout << texte.getString("setTypeCurrent","Set type : ") << c << endl;
        }
      }else{
        cout << texte.getString("typeHelp","invalide syntax") << endl;
      }
    }

    //! commande "gtype"
    else if(commandes[0] == "gtype"){
      string type = "indéfini";
      switch (nix.getType()) {
        case 1: type = "long";
        break;
        case 2: type = "int";
        break;
        case 3: type = "short";
        break;
        case 4: type = "char";
        break;
      }
      cout << texte.getString("type","")  << type << endl;
    }

    //! Commande "search"
    else if( commandes[0] == "search"){
      if (commandes.size() >= 2) {
        int choice=10;
        try{
          choice = stoi(commandes[1]);
        }
        catch (const invalid_argument& ia) {
          std::cerr << texte.error_invalid_argument("search") << std::endl;
        }
        catch (const out_of_range& oor) {
          std::cerr << texte.error_out_of_range("an integer") << std::endl;
        }
        try{
          int returnCode;
          switch(choice){
            case 0:
            case 2:
            case 4:
            case 5:
            returnCode = nix.search(choice, 0, 0);
            if (1 == returnCode) {
              std::cout << to_string(nix.getMapSize()) <<texte.getString("search_info","") << endl;
            } else if (-1 == returnCode) {
              cout << texte.missing_argument("search") << endl;
            } else {
              std::cout << texte.getString("isrunning","running") << std::endl;
            }
            std::cout << to_string(nix.getMapSize()) <<texte.getString("search_info","") << endl;
            break;
            case 1:
            case 3:
            case 7:
            if (commandes.size() >= 3) {
              long value = stol(commandes[2]);
              returnCode = nix.search(choice, value, 0);
              if (1 == returnCode) {
                std::cout << to_string(nix.getMapSize()) <<texte.getString("search_info","") << endl;
              } else if (-1 == returnCode) {
                cout << texte.missing_argument("search") << endl;
              } else {
                std::cout << texte.getString("isrunning","running") << std::endl;
              }
            }
            else {
              cout << texte.missing_argument("") << endl;
            }
            break;
            case 6:
            if (commandes.size() >= 4)  {
              long lbound, hbound;
              lbound = stol(commandes[2]);
              hbound = stol(commandes[3]);
              returnCode = nix.search(choice, lbound, hbound);
              if (1 == returnCode) {
                std::cout << to_string(nix.getMapSize()) <<texte.getString("search_info","") << endl;
              } else if (-1 == returnCode) {
                cout << texte.missing_argument("search") << endl;
              } else {
                std::cout << texte.getString("isrunning","running") << std::endl;
              }
            }
            else {
              cout << texte.missing_argument("search") << endl;
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
          std::cerr << texte.error_out_of_range("a long") << std::endl;
        }
      }
      else {
        cout <<  texte.search_help() << endl;
      }
    }

    //! Commande "store"
    else if ( commandes[0] == "store") {
      if (commandes.size() >= 2) {
        try{
          long adresse = stol(commandes[1],NULL,16);
          nix.store(adresse);
        }
        catch (const invalid_argument& ia) {
          std::cerr << texte.getString("store_help","invalid_argument") << std::endl;
        }
        catch (const out_of_range& oor) {
          std::cerr << texte.getString("store_help","out_of_range") << std::endl;
        }
      }
    }


    //! Commande "list", affiche les n valeurs trouver après recherche
    else if( commandes[0] == "list"){
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
    }

    else if( commandes[0] == "stringSearch"){
      map<void * , char> m = nix.stringSearcher(commandes[1]);
      int num = 0;
      for(auto it = m.begin(); it != m.end(); ++it){
        cout << num << " : (" << it->first << ") " <<  " ==> " << it->second  << endl;
        num++;
      }
    }

    //! Commande "list_store"
    else if ( commandes[0] == "list_store") {
      int size = 10;
      if ((commandes.size() >= 2))
      {
        try{
          size = stoi(commandes[1]);
        }
        catch (const invalid_argument& ia) {
        }
        catch (const out_of_range& oor) {
          std::cerr << texte.error_out_of_range("an integer") << std::endl;
        }
      }
      map<void * , long> m = nix.list_store(size);
      int num = 0;
      for(auto it = m.begin(); it != m.end(); ++it){
        cout << num << " : (" << it->first << ") " <<  " ==> " << it->second  << endl;
        num++;
      }
    }

    //! Commande "alter"
    else if( commandes[0] == "alter"){
      if (commandes.size() >= 3) {
        try{
          long n;
          long v;
          n = stol(commandes[1],NULL,16);

          v = stol(commandes[2],NULL,10);
          int returnCode = nix.replace(n, v);
          if (1 == returnCode) {
            std::cout << texte.getString("alter_Success","Success") << '\n';
          }else if(-1 == returnCode){
            std::cout << texte.getString("alter_fail","Fail") << '\n';
          }else{
            std::cout << texte.getString("isrunning","running") << std::endl;
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

    //! commande "fstart"
    else if( commandes[0] == "fstart"){
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
    //! Commande "help" ou Commande inconue
    else{
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

string customLine(int type) {
  string stype = "indéfini";
  switch (type) {
    case 1: stype = "long";
    break;
    case 2: stype = "int";
    break;
    case 3: stype = "short";
    break;
    case 4: stype = "char";
    break;
  }
  return "type : \033[1;33m" + stype +"\033[0m > ";
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
