# Nixwen
## À propos de Nixwen

## Commandes
* `exit` -- Quitter le programme
* `cont` -- Reprendre l'exécution du programme
* `stop` -- Stoper l'exécution du programme
* `fuzzysearch` -- Initialiser une recherche fuzzy
* `search` -- Continuer une recherche commencer avec fsearch ou fuzzysearch
* `list` -- Afficher les résultats de la recherche
* `fstart` -- Reprendre l'exécution du programme puis le stopper 1 seconde plus tard
* `alter` -- Modifier le contenu à une adresse choisi parmi les addresses proposées par la commande list
* `type` -- Modifie le type lors des recherche. (choix parmi : long | int | short | char ) 
* `gtype` -- Affiche le type courrant des future recherches
* `store` -- Sauvegarde une addresse qui est affiché par list
* `list_store` -- Affiche les l'élements enregistrés avec store
* `help` -- Afficher les commandes disponibles

## TODO
* [voir wiki](https://github.com/IUT-MemScanner/nixwen/wiki/projet-S4)
* Pouvoir spécifier un pid à attacher au lieu de lancer un nouveau programme => Imposible avec un ordinateur de l'IUT (LSM yama/ptrace_scope)

## Installation et utilisation
Installer avec git: 
  ``` bash
  git clone https://github.com/IUT-MemScanner/nixwen.git
  cd nixwen
  make
```
Utilisation :   
Dans le dossier, saisir la commande :
``` bash
./nixwen programme
```
"programme" est le programme que vous souhaitez observer.


## Programme de test `dummy`

Aller dans le dossier contenant le programme (par défaut sous `nixwen/dummy/qt/`)
```bash
cd dummy/qt/
```
Puis créer le Makefile avec `qmake`
```bash
qmake
```
Enfin, exécuter le makefile :
```bash
make
```
L'exécutable généré aura alors pour nom "dummy".
