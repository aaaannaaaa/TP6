//
// Created by joyen on 21/10/2022.
//

//GIT: https://github.com/aaaannaaaa/TP6

#include "graphe.h"

int main() {
    Graphe * G=lire_graphe("TP6.txt");
    afficher_graphe(G);
    G=fordFulkerson(G);
    printf("Calcul flot max\n");
    calculFlotMax(G, rechercheSource(G));
    return 0;
}
