/**
* \file      commands.cpp
* \version   2.0
* \brief     Définit les commandes qu'utilise nixwen pour rechercher en mémoire
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "commands.h"

/**
* \fn initialise une recherche. Parcoure la mémoire et remplis une map contenant
* les adresses et leur valeurs actuelles en mémoire
*/
map<void *, long> fuzzsearch(long pid, map<void *, long> memoire, int type) {
  // init

  void *b = getDebutStack(pid);
  void *e = getFinStack(pid);
  void *pointer = b;

  while (pointer < e) {

    switch (type) {
    case 1:
      memoire[pointer] = ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
      pointer = (void *)((long)pointer + sizeof((long)(0)));
      break;
    case 2:
      memoire[pointer] =
          (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((int)(0)));
      break;
    case 3:
      memoire[pointer] =
          (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((short)(0)));
      break;
    case 4:
      memoire[pointer] =
          static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((char)(0)));
      break;
    }
  }

  pointer = getDebutHeap(pid);
  e = getFinHeap(pid);

  while (pointer < e) {
    switch (type) { // incrémente le pointeur en fonction du type actuel
    case 1:
      memoire[pointer] = ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
      pointer = (void *)((long)pointer + sizeof((long)(0)));
      break;
    case 2:
      memoire[pointer] =
          (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((int)(0)));
      break;
    case 3:
      memoire[pointer] =
          (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((short)(0)));
      break;
    case 4:
      memoire[pointer] =
          static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((char)(0)));
      break;
    }
  }

  pointer = getDebutData(pid);
  e = getFinData(pid);
  while (pointer < e) {
    switch (type) { // incrémente le pointeur en fonction du type actuel
    case 1:
      memoire[pointer] = ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
      pointer = (void *)((long)pointer + sizeof((long)(0)));
      break;
    case 2:
      memoire[pointer] =
          (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((int)(0)));
      break;
    case 3:
      memoire[pointer] =
          (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((short)(0)));
      break;
    case 4:
      memoire[pointer] =
          static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
      pointer = (void *)((long)pointer + sizeof((char)(0)));
      break;
    }
  }
  return memoire;
}

/**
* \fn Raffine une map en fonction des parametres
* codeOperation codes
* 0 : +   the value is greater
* 1 : +?  the value is greater by
* 2 : -   the value is lower
* 3 : -?  the value is lower by
* 4 : =   the value is the same
* 5 : /=  the value has changed
* 6 : ><  in between comparison
*/
map<void *, long> fuzzsearch(int codeOperation, map<void *, long> memoire,
                             long value1, long value2, long pid,
                             int type) { // search
  map<void *, long> newM = {};
  long n;
  for (auto it = memoire.begin(); it != memoire.end(); ++it) {
    switch (type) {
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
      n = static_cast<long>(
          (char)ptrace(PTRACE_PEEKDATA, pid, it->first, NULL));
      break;
    }
    switch (codeOperation) {
    case 0:
      if (it->second < n)
        newM[it->first] = n;
      break;
    case 1:
      if (it->second + value1 == n)
        newM[it->first] = n;
      break;
    case 2:
      if (it->second > n)
        newM[it->first] = n;
      break;
    case 3:
      if (it->second - value1 == n)
        newM[it->first] = n;
      break;
    case 4:
      if (it->second == n)
        newM[it->first] = n;
      break;
    case 5:
      if (it->second != n)
        newM[it->first] = n;
      break;
    case 6:
      if (n > value1 && n < value2)
        newM[it->first] = n;
      break;
    case 7:
      if (n == value1)
        newM[it->first] = n;
      break;
    default:
      break;
    }
  }
  return newM;
}


  /*!
     \brief "recherche d'un string"
     \return "Retourne une map de charactère"
  */
map<void *, char> stringSearch(string value, long pid) {
  map<void *, char> memoire = {};
  void *b = getDebutStack(pid);
  void *e = getFinStack(pid);
  void *pointer = b;

  while (pointer < e) {
        memoire[pointer] = (char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
        pointer = (void *)((long)pointer + sizeof((char)(0)));
  }

  pointer = getDebutHeap(pid);
  e = getFinHeap(pid);
  while (pointer < e) {
              memoire[pointer] = (char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
              pointer = (void *)((long)pointer + sizeof((char)(0)));
  }
  pointer = getDebutData(pid);
  e = getFinData(pid);
  while (pointer < e) {
              memoire[pointer] = (char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
              pointer = (void *)((long)pointer + sizeof((char)(0)));
  }
  return memoire;
}

/**
* \fn getter d'une valeur à une addresse
* type
* 1 : long  (64b - 8o)
* 2 : int   (32b - 4o)
* 3 : short (16b - 2o)
* 4 : char  (8b  - 1o)
*/
long get(void *pointer, int type, long pid) {
  switch (type) {
  case 1:
    return ptrace(PTRACE_PEEKDATA, pid, pointer, NULL);
  case 2:
    return (long)((int)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
  case 3:
    return (long)((short)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
  case 4:
    return static_cast<long>((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
  case 5:
    return (long)((char)ptrace(PTRACE_PEEKDATA, pid, pointer, NULL));
  default:
    return 0xDEADBEEF;
  }
}

// alter a value with a new value
/**
* \fn modifie une valeur à une addresse par une autre valeur d'un type
* type
* 1 : long  (64b - 8o)
* 2 : int   (32b - 4o)
* 3 : short (16b - 2o)
* 4 : char  (8b  - 1o)
*/
bool alter(void *pointer, long newvalue, long pid, int type) {
  long curV = get(pointer, 1, pid);
  switch (type) {
  case 1:
    return ptrace(PTRACE_POKEDATA, pid, pointer, newvalue) != -1;
    break;
  case 2:
    return ptrace(PTRACE_POKEDATA, pid, pointer,
                  (curV & 0xFFFFFFFF00000000) +
                      (newvalue)) != -1;
    break;
  case 3:
    return ptrace(PTRACE_POKEDATA, pid, pointer,
                  (curV & 0xFFFFFFFFFFFF0000) +
                      (newvalue)) != -1;
    break;
  case 4:
    return ptrace(PTRACE_POKEDATA, pid, pointer,
                  (curV & 0xFFFFFFFFFFFFFF00) +
                      (newvalue)) != -1;
    break;
  default:
    return false;
    break;
  }
}
