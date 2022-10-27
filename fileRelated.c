//
// Created by alexi on 24/10/2022.
//

#include "fileRelated.h"

//Fonction File//
t_file* creation()
{
    t_file* f=(t_file*)malloc(sizeof(t_file));
    f->maillon_a_defiler=NULL;
    f->maillon_a_enfiler=NULL;
    return f;
}

int estVide(t_file* fAttente)
{
    if (fAttente->maillon_a_defiler == NULL && fAttente->maillon_a_enfiler == NULL)
        return 1;
    else
        return 0;
}


t_file* enfiler(t_file *f,t_id_sommet* nouv)
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
    return f;
}
//o
t_file* defiler(t_file* f, t_id_sommet** res)
{
    t_maillon* temp=NULL;

    if(estVide(f)==1)
    {
        printf("il n'y a aucun element a supp\n");
        return NULL;
    }
    else
    {
        temp=f->maillon_a_defiler;
        *res=f->maillon_a_defiler->s;
        if(f->maillon_a_defiler==f->maillon_a_enfiler)
        {
            f->maillon_a_enfiler=NULL;
            f->maillon_a_defiler=NULL;
            free(temp);
        }
        else
        {
            f->maillon_a_defiler=f->maillon_a_defiler->prev;
            f->maillon_a_defiler->next=NULL;
            free(temp);
        }
        return f;
    }
}

int conditionFin(t_id_sommet* s, char puit)
{
    if(s->lettre==puit)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void afficherListe(t_file* f)
{
    t_maillon* parcours=f->maillon_a_enfiler;
    if(estVide(f))
    {
        printf("La liste est vide rien a afficher\n");
    }
    else
    {
        while(parcours!=NULL)
        {
            printf("%c\n", parcours->s->lettre);
            parcours=parcours->next;
        }
    }

}