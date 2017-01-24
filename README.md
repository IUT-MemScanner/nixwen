# Nixwen
## À propos de Nixwen

## Commandes
* `exit` -- Quitter le programme
* `cont` -- Reprendre l'exécution du programme
* `stop` -- Stoper l'exécution du programme
* `fsearch` -- Initialiser une recherche
* `fuzzysearch` -- Initialiser une recherche fuzzy
* `search` -- Continuer une recherche commencer avec fsearch ou fuzzysearch
* `list` -- Afficher les résultats de la recherche
* `size` --  Definir la taille des données à rechercher
* `alter` -- Modifier le contenu à une adresse choisi parmi celles proposées par la commande list
* `help` -- Afficher les commandes disponibles

## FIXME
* problème alter lorsqu'on veut mettre une valeur entre 0 < x < 10
* premier search, la valeur recherchée ne s'y trouve pas
* lors de search les premières valeurs affichés ne sont pas cohérentes

## TODO
* Implémenter size
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
