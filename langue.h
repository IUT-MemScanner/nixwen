#ifndef LANGUE_H_INCLUDED
#define LANGUE_H_INCLUDED
#include <iostream>

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
  string fuzzysearch_msg();
  string alter_msg(string);
  string welcome_msg();

private:
  string langue = "fr";
  string interface = "tui";
  string get(string aide);
  map<string, string> conf;
  bool load(string file);
  string getString(string key, string def);
};

#endif // LANGUE_H_INCLUDED
