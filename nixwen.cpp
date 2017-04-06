/**
* \file      nixwen.cpp
* \version   2.0
* \brief     moteur du programme nixwen
*/

#include "nixwen.hpp"

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
    Nixwen::type = 1;
    Nixwen::nextType = Nixwen::type;
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
    Nixwen::type = Nixwen::nextType;
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

/**
* \brief     enregistre une adresse mérmoire avec le type courant de recherche
* \param     addresse      long représentant une adresse
* \return    int 1 si succes sinon -1 echec
*/
int Nixwen::store(long addresse) {
  try{
    mapR[(void*)addresse];
    Nixwen::mapStore.emplace((void*)addresse, Nixwen::type);
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
    mymap.insert ( std::pair<void *,long>(it->first,get(it->first, Nixwen::type, Nixwen::pid)) );
    num++;
  }
  return mymap;
}

map<void *, char>  Nixwen::stringSearcher(string value){
  return stringSearch(value, Nixwen::pid);
}


/**
*
*/
map<void *, pair<long, int>> Nixwen::list_store(int length) {
  map<void *, pair<long, int>> mymap;
  int num = 0;
  for(auto it = Nixwen::mapStore.begin(); it != Nixwen::mapStore.end() && num < length; ++it){
    mymap.insert( pair<void *, pair<long,int> >(it->first, make_pair( get(it->first, it->second, Nixwen::pid), it->second)));
    num++;
  }
  return mymap;
}


/**
* \brief     modifie une valeur a une addresse par une valeur
* \param     pointer     long représente l'addresse de la valeur à modifié
* \param     pointer     long nouvelle valeur (sera cast dans le type définit dans nixwen)
* \return    int : 1 = succes, -1 = pointer non trouver, -2 = le programme suivie n'est pas stopper
*/
int Nixwen::replace(long pointer, long newValue)
{
  if (!Nixwen::running) {
    if(Nixwen::mapStore.end() != Nixwen::mapStore.find((void*)pointer)){
      alter((void*)pointer, newValue, Nixwen::pid, Nixwen::mapStore[(void*)pointer]);
      return 1; //sucess
    }else if(Nixwen::mapR.end() != Nixwen::mapR.find((void*)pointer)){
      alter((void*)pointer, newValue, Nixwen::pid, Nixwen::type);
      return 1; //sucess
    }else{
      return -1; // fail, pointer not found
    }
  }
  return -2; // fail, , child is not stopped
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
* \brief     getter du type
* \return    int le type
*/
int Nixwen::getType(){
  return Nixwen::type;
}


/**
* \brief     affecte un nouveau type a la prochaine recherche
* \param     type    int  0 = long; 1 = int ; 2 = short ; 3 = char
* \return    int : 1 si succes sinon -1
*/
int Nixwen::setType(int type){
  switch (type) {
    case 1:
    case 2:
    case 3:
    case 4:
    Nixwen::nextType = type;
    return 1;
  }
  return -1;
}

/**
* \brief     affecte un nouveau type a la recherche courrante
* \param     type    int  0 = long; 1 = int ; 2 = short ; 3 = char
* \return    int : 1 si succes sinon -1
*/
int Nixwen::setCurrentType(int type){
  switch (type) {
    case 1:
    case 2:
    case 3:
    case 4:
    Nixwen::type = type;
    return 1;
  }
  return -1;
}
