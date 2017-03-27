/**
 * \file      langue.cpp
 * \version   2.0
 * \brief     classe de recherche de string dans un fichier de config
 */


#include "langue.h"



//using namespace std;
/**
 *   \brief "constru"
 *   \brief "Description"
 *   \param langue    string langue du fichier a charger de préférence
 *   \param interface    string interface
 */

Langue::  Langue(string langue, string interface)
{
  Langue::langue = langue;
  Langue::interface = interface;
  if (langue == "fr") {
    load("ressource/conf_fr.cfg");
  }
  else
  {
    load("ressource/conf_fr.cfg");
  }
}

// format du fichier compris key=definition
bool Langue::load(string file)
{
    ifstream f(file);
    string str = "";
    vector<string> vect;
    Langue::conf.clear();

    if(!f.is_open())
        return false;

    while(!f.eof())
    {
        getline(f, str);

        if(str.empty() || str[0] == COMM_CHAR)
            continue;
        // spltit à tous les carractères '=' puis si des '=' se trouve dans la parti definition (droite), les laisser
        vect = utils::explode(str, "=");
        if (vect.size() > 2)
        {
          std::string s;
          std::for_each(vect.begin()+1, vect.end(), [&](const std::string &piece){ s += piece+"="; });
          s.pop_back();
          vect[1]=s;
          vect.erase (vect.begin()+2,vect.end());
        }
        if(vect.size() == 2)
        {
            vector<string> v = utils::explode(vect[1],"\\n");
            std::string s;
            std::for_each(v.begin(), v.end(), [&](const std::string &piece){ s += piece + "\n"; });
            s.pop_back();
            vect[1]=s;
            if(getString(vect[0], "") != "")
                clog << "Erase config"+vect[0]+" "+getString(vect[0], "")+" by "+vect[1] << endl;
            //clog << "Config loaded "+vect[0]+" "+vect[1] << endl;
            Langue::conf.insert(pair<string, string>(vect[0], vect[1]));
        }
        else
        {
            cerr << "Trying to load a invalide config at :" + vect[0] << endl;
        }
      }
    f.close();
    return true;
}


string Langue::getString(string key, string def)
{
    try
    {
        return Langue::conf.at(key);
    }
    catch(out_of_range e)
    {
      //std::cerr << "Out of Range error: " + key + " n'existe pas ("  << ")"<< '\n';
    }
    return def;
}


string Langue::error_invalid_argument(string commande)
{
  if (commande == "search")
  {
    return getString("error_invalid_argument_search","");
  }
  else if (commande == "alter")
  {
    return getString("error_invalid_argument_alter","");
  }
  else if (commande == "fstart")
  {
    return getString("error_invalid_argument_fstart","");
  }
  else {
    return getString("error_invalid_argument","");
  }
}

// erreur "out of range"
string Langue::error_out_of_range(string type)
{
  return getString("error_out_of_range","")+ type ;
}


// liste des commandes
string Langue::quick_help()
{
  return getString("quick_help","");
}

string Langue::search_help()
{
  return getString("search_help","");
}

string Langue::missing_argument(string commande)
{
  if (commande == "alter") {
    return getString("missing_argument_alter","argument manquant");
  }
  else if(commande == "search")
  {
    return getString("missing_argument_search","argument manquant");
  }
  else
  {
    return getString("missing_argument","argument manquant");
  }
}

string Langue::alter_msg(string msg)
{
  if (msg == "boundary") {
    return getString("alter_boundary","");
  }
  else if (msg == "not_found")
  {
    return getString("alter_not_found","");
  }
  else
  {
    return "texte non trouvé";
  }
}


std::string Langue::welcome_msg()
{
  return getString("welcome_msg","");
}
