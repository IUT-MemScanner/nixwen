/**
 * \file      langue.h
 * \version   2.0
 * \brief     header de la classe de recherche de string dans un fichier de config
 */
#ifndef LANGUE_H_INCLUDED
#define LANGUE_H_INCLUDED
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include "utils.hpp"

#define COMM_CHAR '#'

using namespace std;

class Langue
{
public:
  Langue(string langue, string interface);
  string getLangue();
  string getinterface();
  string error_invalid_argument(string commande);
  string error_out_of_range(string type);
  string quick_help();
  string search_help();
  string missing_argument(string commande);
  string alter_msg(string);
  string welcome_msg();
  string getString(string key, string def);

private:
  string langue = "fr";
  string interface = "tui";
  map<string, string> conf;
  bool load(string file);
};

#endif // LANGUE_H_INCLUDED
