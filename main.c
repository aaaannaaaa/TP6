#include "graphe.h"

int main() {
    Graphe * G=lire_graphe("TP6.txt");
    afficher_graphe(G);
    return 0;
}
