//
// Created by alexi on 24/10/2022.
//

#include "fileRelated.h"

//Fonction File//
int estVide(t_file* fAttente)
{
    if (fAttente->maillon_a_defiler == NULL && fAttente->maillon_a_enfiler == NULL)
        return 1;
    else
        return 0;
}


void enfiler(t_file *f,t_id_sommet nouv)
{
    t_maillon* nouveau;

    nouveau=(t_maillon*)malloc(sizeof(t_maillon));
    if(nouveau==NULL)
    {
        printf("pb d'allocation Dyn de maillon\n");
    }
    else
    {
        nouveau->s=nouv;
        nouveau->next=NULL;
        nouveau->prev=NULL;

        if(estVide(f)==1)
        {
            //liste vide
            f->maillon_a_enfiler=nouveau;
            f->maillon_a_defiler=nouveau;
        }
        else
        {
            f->maillon_a_enfiler->prev=nouveau;
            nouveau->next=f->maillon_a_enfiler;
            f->maillon_a_enfiler=nouveau;
        }
    }
}

t_id_sommet defiler(t_file* f)
{
    t_maillon* ptcourant=NULL;
    t_maillon* ptprecedent=NULL;
    t_id_sommet res;

    if(estVide(f)==1)
    {
        printf("il n'y a aucun element a supp\n");
        return NULL;
    }
    else
    {
        f->maillon_a_defiler
        return res;
    }
}