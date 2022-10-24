//
// Created by joyen on 21/10/2022.
//

#ifndef TP6_GRAPHE_H
#define TP6_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct id_sommet
{
    char lettre;
    int marque;//pour DFS
    int pred;
}t_id_sommet;


typedef struct Graphe
{
    int ordre;
    t_id_sommet* tab_sommet;//tableau de sommet
    int **mat_capacite;
    int **mat_flot;
} Graphe;


Graphe* CreerGraphe(int ordre);
Graphe * lire_graphe(char * nomFichier);
void afficher_graphe(Graphe * graphe);
#endif //TP6_GRAPHE_H
