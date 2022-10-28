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
    int position;
}t_id_sommet;


typedef struct Graphe
{
    int ordre;
    t_id_sommet** tab_sommet;//tableau de sommet dynamique
    int **mat_capacite;//matrice de capacité
    int **mat_flot;//matrice des flots actuels
} Graphe;
//o

Graphe* CreerGraphe(int ordre);
Graphe * lire_graphe(char * nomFichier);
t_id_sommet* rechercheSource(Graphe* g);
t_id_sommet* recherchePuit(Graphe* g);
int rechercheFlotMax(Graphe* g, t_id_sommet* depart);//depart qu'on retrouve en utilisant recherche
Graphe* MaJFlotGraphe(Graphe* g, t_id_sommet* depart, int flotMax);
Graphe* BFS(Graphe* g, int* verifFin);
Graphe* fordFulkerson(Graphe* g);
void calculFlotMax(Graphe* g, t_id_sommet* source);
void afficher_graphe(Graphe * graphe);
#endif //TP6_GRAPHE_H
