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
//il manque un truc, comment reconnaitre le puit ou la source?, on regarde les sommets entrant et les sommets sortant, si il n'a pas de sommet entrant dans la matrice c'est une source si il n'a pas de sommet sortant c'est un puit;