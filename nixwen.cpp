
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
  }
}

int Nixwen::getPid(){
  return Nixwen::pid;
}

int Nixwen::init(){
  if (!Nixwen::running) {
    Nixwen::currentSize = dataSize;
    Nixwen::mapR = fuzzsearch(Nixwen::pid, Nixwen::mapR);
    return Nixwen::mapR.size();
  }
  return -1;
}

int Nixwen::search(int choice, long firstValue, long secondValue)
{
  if (!Nixwen::running) {
    switch (choice)
    {
      case 0:
      case 2:
      case 4:
      case 5:
      mapR = fuzzsearch(choice, Nixwen::mapR, 0, 0, Nixwen::pid);
      break;
      case 1:
      case 3:
      case 7:
      mapR = fuzzsearch(choice, Nixwen::mapR, firstValue, 0, pid);
      break;
      case 6:
      long lbound, hbound;
      lbound = firstValue;
      hbound = secondValue;
      Nixwen::mapR = fuzzsearch(6, Nixwen::mapR, lbound, hbound, Nixwen::pid);
      break;
      default:
      return -1;
    }
    return 1;
  }
  return -2;
}

map<void *, long> Nixwen::list(int length)
{
  std::map<void *, long> mymap;
  int num = 0;
  for(auto it = Nixwen::mapR.begin(); it != Nixwen::mapR.end() && num < length; ++it){
    mymap.insert ( std::pair<void *,long>(it->first,(ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF)) );
    //cout << num << " : (" << it->first << ") " << it->second  << " ==> " << (ptrace(PTRACE_PEEKDATA, pid, it->first, NULL) & 0xFFFFFFFF) << endl;
    num++;
  }
  return mymap;
}

int Nixwen::replace(long pointer, long newValue)
{
      long n;
      long v;
      n = pointer;

      if(Nixwen::mapR.end() != Nixwen::mapR.find((void*)n)){
        v = newValue;
        if(v <= pow(2,Nixwen::currentSize)) {
          alter((void*)n, v, Nixwen::pid); }
        else{
          // cout << texte.alter_msg("boundary") << endl;
          return 3;
          }
      }else{
//        cout << texte.alter_msg("not_found") << endl;
        return 2;
      }
      return 1;
}


int Nixwen::cont()
{
  if (!Nixwen::running) {
    ptrace(PTRACE_CONT, Nixwen::pid, NULL, SIGCONT);
    Nixwen::running = true;
    return 1;
  }else{
    return -1;
  }
}

int Nixwen::stop()
{
  if (Nixwen::running) {
    int status = 0;
    kill(Nixwen::pid, SIGSTOP);
    wait(&status);
    Nixwen::running = false;
    return 1;
  }else{
    return -1;
  }
}

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
  return 1;
}

int Nixwen::quit(){
  kill(Nixwen::pid, 9); // Be sure to kill the child
  return 1;
}

int Nixwen::getCurrenSize(){
  return Nixwen::currentSize;
}
