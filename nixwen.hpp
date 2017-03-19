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
/** id type
    1 : long  (64b - 8o)
    2 : int   (32b - 4o)
    3 : short (16b - 2o)
    4 : char  (8b  - 1o)
**/

private:
  bool running;
  int dataSize;
  int currentSize;
  map<void*, long> mapR;
  long pid;
  int type;

};

#endif // NIXWEN_HPP_INCLUDED
