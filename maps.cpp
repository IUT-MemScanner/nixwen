#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
/*fichier*/
#include <dirent.h>
/* isdigit */
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
/*
 * split une chaine string avec un delimiter et modifie un vector
 */
void split(const string &s, char delim, vector<string> &elems) {
   stringstream ss;
   ss.str(s);
   string item;
   while (std::getline(ss, item, delim)) {
      elems.push_back(item);
   }
}

/*
* Récupère le nom du prossessus qui a le pid egale au pid en parametre
*/
string fichier(long pid) {
  string path = "/proc/" + to_string(pid) + "/stat";
  FILE* fichier = fopen(path.c_str(), "r");
  if (fichier != NULL) {
    char sub[50] = "";
    fgets(sub, 50, fichier);
    vector<string> contenu;
    split(sub,' ',contenu);
    string nom = contenu[1];
    nom = nom.substr (1,nom.find(")")-1);
 
    fclose(fichier);
    return nom;
  }
  exit(1);
  return "";
}

/*
* Récupère l'addresse de debut de la pile pour un pid
*/
void * getDebutHeap(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '\\[heap\\]' | cut -d \"-\" -f1").c_str(), "r");
	
	char val[100]; // Stockage du df
	fscanf(fd,"%s",val);	// recupération du df
	return (void *)strtol(val, 0, 16);  // conversion en long depuis base 16
}

/*
* Récupère l'addresse de fin de la pile pour un pid
*/
void * getFinHeap(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '\\[heap\\]' | cut -d ' ' -f1 | cut -d '-' -f2").c_str(), "r");
  
	char val[100];
	fscanf(fd, "%s", val);
	return (void *)strtol(val,0,16);  
}


/*
* Récupère l'addresse de debut de la pile pour un pid
*/
void * getDebutStack(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '\\[stack\\]' | cut -d \"-\" -f1").c_str(), "r");
	
	char val[100]; // Stockage du df
	fscanf(fd,"%s",val);	// recupération du df
	return (void *)strtol(val, 0, 16);  // conversion en long depuis base 16
}

/*
* Récupère l'addresse de fin de la pile pour un pid
*/
void * getFinStack(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '\\[stack\\]' | cut -d ' ' -f1 | cut -d '-' -f2").c_str(), "r");
  
	char val[100];
	fscanf(fd, "%s", val);
	return (void *)strtol(val,0,16);  
}

/*
* Récupère l'addresse de début du tas pour un pid
*/
void * getDebutProc(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '"+fichier(pid)+"$' | head -1 | cut -d '-' -f1").c_str(), "r");
	
	char val[100];
	fscanf(fd, "%s", val);
	return (void *)strtol(val,0,16);  
}

/*
* Récupère l'addresse de fin du tas pour un pid
*/
void * getFinProc(long pid){
	FILE* fd = popen(("cat /proc/"+to_string(pid)+"/maps | grep '"+fichier(pid)+"$' | tail -1 | cut -d ' ' -f1 | cut -d '-' -f2").c_str(), "r");
	
	char val[100];
	fscanf(fd, "%s", val);
	return (void *)strtol(val,0,16);  
}

/*
* Affiche sur la sortie standard tous les processus démarrés
*/
void ls(){
  struct dirent *lecture;
  DIR *rep;
  rep = opendir("/proc" );
  while ((lecture = readdir(rep))) {
    if (isdigit(lecture->d_name[0])){
      cout << lecture->d_name << " : " << fichier(strtol(lecture->d_name,0,10)) << endl;
    }
  }
  closedir(rep);
}
