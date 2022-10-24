//
// Created by alexi on 24/10/2022.
//

#ifndef TP6_FILERELATED_H
#define TP6_FILERELATED_H

#include "graphe.h"

typedef struct maillon
{
    t_id_sommet s;
    struct maillon* next;
    struct maillon* prev;
}t_maillon;

typedef struct file
{
    struct maillon* maillon_a_enfiler;
    struct maillon* maillon_a_defiler;
}t_file;

int estVide(t_file* fAttente);
void enfiler(t_file *f,t_id_sommet nouv);

#endif //TP6_FILERELATED_H
