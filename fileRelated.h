//
// Created by alexi on 24/10/2022.
//

#ifndef TP6_FILERELATED_H
#define TP6_FILERELATED_H

#include "graphe.h"

typedef struct maillon
{
    t_id_sommet* s;
    struct maillon* next;
    struct maillon* prev;
}t_maillon;
//o
typedef struct file
{
    struct maillon* maillon_a_enfiler;
    struct maillon* maillon_a_defiler;
}t_file;

int estVide(t_file* fAttente);
t_file* creation();
t_file* enfiler(t_file *f,t_id_sommet* nouv);
int conditionFin(t_id_sommet* s, char puit);
t_file* defiler(t_file* f, t_id_sommet** res);
void afficherListe(t_file* f);

#endif //TP6_FILERELATED_H
