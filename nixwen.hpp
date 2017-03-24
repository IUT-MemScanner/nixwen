/**
 * \file      nixwen.hpp
 * \version   2.0
 * \brief     header moteur du programme nixwen
 */
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
  void setType(int type);

private:
  bool running;
  int dataSize;
  int currentSize;
  map<void*, long> mapStore;
  map<void*, long> mapR;
  long pid;
  int type;
};

#endif // NIXWEN_HPP_INCLUDED
