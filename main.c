#include "graphe.h"

int main() {
    Graphe * G=lire_graphe("TP6.txt");
    afficher_graphe(G);
    return 0;
}

/*prochaine étape :
 1/création des arretes à partir de la matrice
 2/création du BFS revisité pour notre problème(la condition de fin est quand le puit est rajouté dans la file)
 3/cration de l'algorithme de FordFulkerson(jsp pour l'orthographe) et implémentation en C
*/