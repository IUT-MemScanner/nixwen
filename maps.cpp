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


string fichier(string pid) {
  string path = "/proc/" + pid + "/stat";
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

long getDebutStack(string pid){
	FILE* fd = popen(("cat /proc/"+pid+"/maps | grep '\\[stack\\]' | cut -d \"-\" -f1").c_str(), "r");
	
	char val[100]; // Stockage du df
	fscanf(fd,"%s",val);	// recupération du df
	return strtol(val, 0, 16);  // conversion en long depuis base 16
}

long getFinStack(string pid){
	FILE* fd = popen(("cat /proc/"+pid+"/maps | grep '\\[stack\\]' | cut -d ' ' -f1 | cut -d '-' -f2").c_str(), "r");
  
	char val[100];
	fscanf(fd, "%s", val);
	return strtol(val,0,16);  
}

long getDebutProc(string pid){
	FILE* fd = popen(("cat /proc/"+pid+"/maps | grep '"+fichier(pid)+"$' | head -1 | cut -d '-' -f1").c_str(), "r");
	
	char val[100];
	fscanf(fd, "%s", val);
	return strtol(val,0,16);  
}

long getFinProc(string pid){
	FILE* fd = popen(("cat /proc/"+pid+"/maps | grep '"+fichier(pid)+"$' | tail -1 | cut -d ' ' -f1 | cut -d '-' -f2").c_str(), "r");
	
	char val[100];
	fscanf(fd, "%s", val);
	return strtol(val,0,16);  
}


void ls(){
  struct dirent *lecture;
  DIR *rep;
  rep = opendir("/proc" );
  while ((lecture = readdir(rep))) {
    if (isdigit(lecture->d_name[0])){
      cout << lecture->d_name << " : " << fichier(lecture->d_name) << endl;
    }
  }
  closedir(rep);
}


// Va disparaitre pour laisser place à un .h + .cpp
int main(int argc, char *argv[]){
  if(argc > 1){
	string pid = argv[1];
    cout << "stk : " << hex << getDebutStack(pid)  << "\tend : " << hex << getFinStack(pid) << endl ;
	cout << "prg : " << hex << getDebutProc(pid) << "\tend : " << getFinProc(pid) << endl;
  }else{
    ls();
  }
  return 0;
}
