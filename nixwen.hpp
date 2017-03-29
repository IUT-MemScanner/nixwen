/**
 * \file      nixwen.hpp
 * \version   2.0
 * \brief     header moteur du programme nixwen
 */
#ifndef NIXWEN_HPP_INCLUDED
#define NIXWEN_HPP_INCLUDED

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
#include "commands.h"


using namespace std;

class Nixwen
{
public:
  Nixwen(int argc, char *argv[],char* en[]);
  int search(int choice, long firstValue, long secondValue);
  int store(long addresse);
  map<void *, long>list(int length);
  map<void *, long>list_store(int length);
  int replace(long pointer, long newValue);
  int cont();
  int stop();
  int fstart(int time);
  int quit();
  int getMapSize();
  int getPid();
  int init();
  int getType();
  int setType(int type);
  int setCurrentType(int type);
  map<void *, char> stringSearcher(string value);

private:
  bool running;
  map<void*, int> mapStore;
  map<void*, long> mapR;
  long pid;
  int type;
  int nextType;
};

#endif // NIXWEN_HPP_INCLUDED
