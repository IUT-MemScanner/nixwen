#ifndef NIXWEN_HPP_INCLUDED
#define NIXWEN_HPP_INCLUDED
#include <iostream>

#include <string>
#include <map>

#include "commands.h"


using namespace std;

class Nixwen
{
public:
  Nixwen(int argc, char *argv[],char* en[]);
  int search(int choice, long firstValue, long secondValue);
  map<void *, long>list(int length);
  int replace(long pointer, long newValue);
  int cont();
  int stop();
  int fstart(int time);
  int quit();
  int getCurrenSize();
  int getPid();
  int init();
  int getType();
  void setType(int type);


private:
  bool running;
  int dataSize;
  int currentSize;
  map<void*, long> mapR;
  long pid;
  int type;

};

#endif // NIXWEN_HPP_INCLUDED
