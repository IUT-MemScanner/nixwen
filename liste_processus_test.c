/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>
/*string */
#include <string.h>
/*fichier*/
#include <dirent.h>
/* isdigit */
#include <ctype.h>

//developpez.com
char *str_sub (const char *s, unsigned int start, unsigned int end)
{
   char *new_s = NULL;
   if (s != NULL && start < end)
   {
      new_s = malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL)
      {
         unsigned int i; //modif
         for (i = start; i <= end; i++)
         {
            new_s[i-start] = s[i];
         }
         new_s[i-start] = '\0';
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   return new_s;
}

const char* fichier(char * dossier) {
  char chaine[50] = "/proc/";
  const char ret[50] = "";
  strcat(chaine, dossier);
  strcat(chaine,"/stat" );
  FILE* fichier = fopen(chaine, "r");
  if (fichier != NULL) {
    char sub[50] = "";
    fgets(sub, 50, fichier);
    char* suiteChaine = NULL;
    suiteChaine = strchr(sub, '(')+1;
    int longeur_nom = strlen(suiteChaine)- strlen(strchr(sub, ')'));
    fclose(fichier);
    return str_sub(suiteChaine,0,longeur_nom-1);
  }
  return ret;
}



void ls(){
  struct dirent *lecture;
  DIR *rep;
  rep = opendir("/proc" );
  while ((lecture = readdir(rep))) {
    if (isdigit(lecture->d_name[0])){
      printf("%s : %s \n", lecture->d_name,fichier(lecture->d_name));
    }
  }
  closedir(rep);
}


int main(int argc, char *argv[]){
  if(argc > 1){
     printf("%s\n",fichier(argv[1]));
   fichier(argv[1]);
  }else{
    ls();
  }
  return EXIT_SUCCESS;
}
