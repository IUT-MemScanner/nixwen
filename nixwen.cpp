/**
 * \file      nixwen.cpp
 * \version   2.0
 * \brief     moteur du programme nixwen
 */

#include "nixwen.hpp"
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

Nixwen::Nixwen(int argc, char *argv[], char *en[]) {
  int status = 0;
  char *prog = argv[1];
  char *emp[] = {NULL};

  Nixwen::pid = fork();

  if (Nixwen::pid == 0)
  {
    int m = ptrace(PTRACE_TRACEME, 0, 0, 0);
    int descF = open("nohup", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
    if (m == -1 || descF == -1)
    {
      kill(getppid(), 9);
      exit(255);
    }
    close(STDOUT_FILENO);
    dup2(descF, STDOUT_FILENO);
    execve(prog, emp, en);

    kill(getppid(), 9); // If the child fail, kill his father
  }
  else
  {
    wait(&status);
    Nixwen::running = false;
    Nixwen::dataSize = 16;
    Nixwen::currentSize = 16;
    Nixwen::type = 1;
    Nixwen::cont();
  }
}

/**
 * \brief       Getter du pid du programme suivi
 * \return    un int qui est le pid du processus suivie
 */
int Nixwen::getPid(){
  return Nixwen::pid;
}

/**
*
*/
int Nixwen::init(){
  if (!Nixwen::running) {
    Nixwen::currentSize = dataSize;
    Nixwen::mapR = fuzzsearch(Nixwen::pid, Nixwen::mapR, Nixwen::type);
    return Nixwen::mapR.size();
  }
  return -1; // fail, child is not stop
}


/**
 * \brief       raffine une recherche selon un critère
 * \param    firstValue         valeur si besoin pour la commande (long)
* \param    secondValue         valeur si besoin pour la commande (long)
 * \return    un int, représentant : 1 = succes, -1 = choix non trouver, -2 = l'enfant n'est pas arrêter
 */
int Nixwen::search(int choice, long firstValue, long secondValue)
{
  if (!Nixwen::running) {
    switch (choice)
    {
      case 0:
      case 2:
      case 4:
      case 5:
      mapR = fuzzsearch(choice, Nixwen::mapR, 0, 0, Nixwen::pid, Nixwen::type);
      break;
      case 1:
      case 3:
      case 7:
      mapR = fuzzsearch(choice, Nixwen::mapR, firstValue, 0, pid,Nixwen::type);
      break;
      case 6:
      long lbound, hbound;
      lbound = firstValue;
      hbound = secondValue;
      Nixwen::mapR = fuzzsearch(6, Nixwen::mapR, lbound, hbound, Nixwen::pid,Nixwen::type);
      break;
      default:
      return -1; //fail, choice not found
    }
    return 1; // sucess
  }
  return -2; // fail, child is not stopped
}

int Nixwen::store(long addresse) {
  try{
    mapR[(void*)addresse];
    Nixwen::mapStore.emplace((void*)addresse, get((void*)addresse, Nixwen::type, Nixwen::pid));
    return 1;
  } catch (const out_of_range& oor) {
    return -1;
  }
}


/**
 * \brief     getter une de l'image de la mémoire de n case mémoire
 * \param     length      int représentant le nombres de ligne à retourner
 * \return    une map contenant l'addresse et sa valeur
 */
map<void *, long> Nixwen::list(int length)
{
  std::map<void *, long> mymap;
  int num = 0;
  for(auto it = Nixwen::mapR.begin(); it != Nixwen::mapR.end() && num < length; ++it){
    if (Nixwen::type==1) { // long
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==2) { //int
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==3) {
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==4) {
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid)) );
    }
    num++;
  }
  return mymap;
}

map<void *, long> Nixwen::list_store(int length) {
  map<void *, long> mymap;
  int num = 0;
  for(auto it = Nixwen::mapStore.begin(); it != Nixwen::mapStore.end() && num < length; ++it){
    if (Nixwen::type==1) { // long
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==2) { //int
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==3) {
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid) ));
    }else if (Nixwen::type==4) {
      mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid)) );
    }
    num++;
  }
  return mymap;
}


/**
 * \brief     modifie une valeur a une addresse par une valeur
 * \param     pointer     long représente l'addresse de la valeur à modifié
 * \param     pointer     long nouvelle valeur (sera cast dans le type définit dans nixwen)
 * \return    int : 1 = succes, -1 = pointer non trouver, -2 = pointer hors des bornes
 */
int Nixwen::replace(long pointer, long newValue)
{
      long n;
      long v;
      n = pointer;

      if(Nixwen::mapR.end() != Nixwen::mapR.find((void*)n)){
        v = newValue;
        if(v <= pow(2,Nixwen::currentSize)) { //TOMODIFY
          alter((void*)n, v, Nixwen::pid, Nixwen::type); }
        else{
          return -2; // fail, out of boundary
          }
      }else{
        return -1; // fail, pointer not found
      }
      return 1; //sucess
}


/**
 * \brief     redémarer le programme suivi
 * \return    int : 1 = succes, -1 = l'enfant est déja démarrer
 */
int Nixwen::cont()
{
  if (!Nixwen::running) {
    ptrace(PTRACE_CONT, Nixwen::pid, NULL, SIGCONT);
    Nixwen::running = true;
    return 1;
  }else{
    return -1; // fail, child is not stopped
  }
}

/**
 * \brief     stop le programme suivi
 * \return    int : 1 = succes, -1 = l'enfant est déja stopper
 */
int Nixwen::stop()
{
  if (Nixwen::running) {
    int status = 0;
    kill(Nixwen::pid, SIGSTOP);
    wait(&status);
    Nixwen::running = false;
    return 1; //sucess
  }else{
    return -1; // fail, child is stopped
  }
}


/**
 * \brief     redémare le processus suivi pendant un certains temps
 * \param     int le temps en second avant de redémarer le fils
 * \return    int : 1 = succes (toujour 1)
 */
int Nixwen::fstart(int time)
{
  ptrace(PTRACE_CONT, pid, NULL, SIGCONT);
  Nixwen::running = true;
  int status;
  sleep(time);

  if(Nixwen::running){
    // Caution ! If it happen twice, wait will be stuck !
    kill(pid, SIGSTOP);
    wait(&status);
    Nixwen::running = false;
  }
  return 1; // sucess
}

/**
 * \brief     tuer l'enfant
 * \return    int : 1 = succes (toujour 1)
 */
int Nixwen::quit(){
  kill(Nixwen::pid, 9); // Be sure to kill the child
  return 1; //sucess
}

/**
 * \brief     getter de la taille de la map (de la recherche courrante)
 * \return    int : la taille de la map
 */
int Nixwen::getMapSize(){
  return Nixwen::mapR.size();
}

/**
 * \brief     redémare le processus suivi pendant un certains temps
 * \return    int le type : 0 = long; 1 = int ; 2 = short ; 3 = char
 */
int Nixwen::getType(){
  return Nixwen::type;
}


/**
 * \brief     redémare le processus suivi pendant un certains temps
 * \param     type    int  0 = long; 1 = int ; 2 = short ; 3 = char
 */
void Nixwen::setType(int type){
  Nixwen::type = type;
}
