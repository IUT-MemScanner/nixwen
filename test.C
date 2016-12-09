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



void getDebutStack(string pid){
   string commande = "cd /proc/" + pid + " && cat maps | grep '\[stack\]' | cut -d '-' -f1";
   cout << system(commande.c_str());
}
void getFinStack(){
   cout << system("cat maps | grep '\[stack\]' | cut -d ' ' -f1 | cut -d '-' -f2");
}
 void getDebutProc(){
   cout << system("cat maps | grep 'zsh$' | tail -1 | cut -d ' ' -f1 | cut -d '-' -f2");
}
void getFinProc(){
   cout << system("cat maps | grep 'zsh$' | tail -1 | cut -d ' ' -f1 | cut -d '-' -f2");
}

void memproc(string nom, string pid, vector<string> &mem){
   string path = "/proc/" + pid + "/maps";
   cout << "path : " << path << endl;
   FILE* fichier = fopen(path.c_str(), "r");
   if (fichier != NULL) {
    vector<string> tmp;
    char addr[40], perms[15], offset[15],dev[15],inode[15],pathname[80];
    char *addrdebut;
    char * addrfin;
    fscanf(fichier,"%s %s %s %s %s",addr,perms,offset,dev,inode);
    fscanf(fichier,"%s",pathname);
    printf("1&& : %s %s %s %s %s %s\n",addr,perms,offset,dev,inode,pathname);
    addrdebut=addr;
    split(pathname,'/',tmp);
    cout << nom<< endl;
    while (tmp.back()==nom) {
      printf("%s %s %s %s %s %s\n",addr,perms,offset,dev,inode,pathname);
      addrfin=addr;
      tmp.clear();
      fscanf(fichier,"%s %s %s %s %s",addr,perms,offset,dev,inode);
      fscanf(fichier,"%s", pathname);
      split(pathname,'/',tmp);
    }
    split(addrdebut,'-',tmp);
    mem.push_back(tmp.front());
    split(addrfin,'-',tmp);
    mem.push_back(tmp.back());
    cout << "start at :" << mem[0]<< " end at : "<< mem[1] << endl;
    fclose(fichier);
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
 

    //vector<string> ret;// temporaire
    //memproc(nom,pid,ret);//temporaire
    fclose(fichier);
    return nom;
  }
  return ":'(";
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


int main(int argc, char *argv[]){
  if(argc > 1){
    vector<string>mem;  
    getDebutStack(argv[1]);
    string nom = fichier(argv[1]);
    cout << "le nom du processus : " << fichier(argv[1])<<endl;
    memproc(nom,argv[1],mem);
  }else{
     getDebutStack("11");
    ls();
  }
  return 0;
}
