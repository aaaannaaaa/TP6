//
// Created by joyen on 21/10/2022.
//

#include "graphe.h"
#include "fileRelated.h"
// creer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->tab_sommet=(t_id_sommet **)malloc(ordre*sizeof(t_id_sommet*)); //on crée un tableau rempli par tous nos sommets
    Newgraphe->mat_capacite=(int**)malloc(ordre*sizeof(int*)); //on crée la premiere ligne de la matrice de capacité
    Newgraphe->mat_flot=(int**)malloc(ordre*sizeof(int*));//on crée la premiere ligne de la matrice de flot
    for(int i=0; i<ordre; i++)
    {
        Newgraphe->tab_sommet[i]=(t_id_sommet*)malloc(sizeof(t_id_sommet));
        Newgraphe->mat_capacite[i]=(int*)malloc(ordre*sizeof(int)); //on crée la deuxieme ligne de la matrice de capacité
        Newgraphe->mat_flot[i]=(int*)malloc(ordre*sizeof(int));//on crée la deuxieme ligne de la matrice de flot
    }
    return Newgraphe;
}

Graphe * lire_graphe(char * nomFichier)
{
    int ordre;
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }


    fscanf(ifs,"%d\n",&ordre);

    graphe=CreerGraphe(ordre); // creer le graphe en fonction de son ordre je lis l'odre sur le fichier et je l'affecte à ma valeur ordre de ma struct graphe
    for(int i=0;i<ordre;i++)
    {
        fscanf(ifs,"%c ",&graphe->tab_sommet[i]->lettre);//on rempli notre tableau de sommet par la valeur des sommets qu'on lit dans le fichier
        printf("lettre %d : %c\n", i, graphe->tab_sommet[i]->lettre);
        graphe->tab_sommet[i]->position=i;
    }
    //j'ai rajouté un espace après le %c pour pouvoir lire la valeur qu'on a espacé dans le fichier c'est pour ça que ça buggait
    graphe->ordre=ordre;


    //on remplit la matrice de capa
    for(int i=0;i<ordre;i++)
    {
        for(int j=0;j<ordre;j++)
        {
            fscanf(ifs,"%d",&graphe->mat_capacite[i][j]);//on remplit la case
        }
        //on passe a la ligne suivante du fichier
    }

//o

    return graphe;
}
void afficher_graphe(Graphe * graphe)
{
    printf("%d\n  ",graphe->ordre); //on affiche l'ordre
    for(int i=0; i<graphe->ordre; i++)
    {
        printf("%c\t", graphe->tab_sommet[i]->lettre);
    }
    printf("\n");
    for(int i=0;i<graphe->ordre;i++)
    {
        printf("%c ",graphe->tab_sommet[i]->lettre);//on affiche le noms des sommets
        for(int j=0;j<graphe->ordre;j++)
        {
            printf("%d\t",graphe->mat_capacite[i][j]);
        }
        printf("\n");
    }
}
//on fait un bfs
//on crée un file
t_id_sommet* recherche(Graphe* g, char lettre)
{
    for(int i=0; i<g->ordre; i++)
    {
        if(g->tab_sommet[i]->lettre==lettre)
        {
            return g->tab_sommet[i];
        }
    }
    return NULL;
}

int rechercheFlotMax(Graphe* g, t_id_sommet* depart)//depart qu'on retrouve en utilisant recherche
{
    int flotMax=100;
    int sommetActu=depart->position;
    int sommetPred=-1;
    int tempFlotRestant=0;
    while(g->tab_sommet[sommetActu]->pred!=-1)
    {
        sommetPred=g->tab_sommet[sommetActu]->pred;
        tempFlotRestant=g->mat_capacite[sommetActu][sommetPred];
        if(tempFlotRestant<flotMax)
        {
           flotMax=tempFlotRestant;
        }
        sommetActu=sommetPred;
    }
    return tempFlotRestant;
}


Graphe* MaJFlotGraphe(Graphe* g, t_id_sommet* depart, int flotMax)
{
    int sommetActu=depart->position;
    int sommetPred=-1;
    while(g->tab_sommet[sommetActu]->pred!=-1)
    {
        sommetPred=g->tab_sommet[sommetActu]->pred;
        g->mat_flot[sommetActu][sommetPred]+=flotMax;
        sommetActu=sommetPred;
    }
}

Graphe* BFS(Graphe* g)
{
    t_id_sommet* place, *temp;
    char source='O';
    char puit='T';
    int verif=0;
    for(int i=0; i<g->ordre; i++)
    {
        g->tab_sommet[i]->marque=0;
        g->tab_sommet[i]->pred=-1;
    }
    place=recherche(g, source);
    t_file* f=creation();
    enfiler(f, g->tab_sommet[place->position]);
    g->tab_sommet[place->position]->marque=1;
    while(verif==0)//rajouter si la liste est vide aussi
    {
        temp=defiler(f);
        for(int i=0; i<g->ordre; i++)
        {
            if(g->mat_capacite[temp->position][i]!=0 && g->mat_capacite[temp->position][i]!=g->mat_flot[temp->position][i] && g->tab_sommet[i]->marque==0)
            {
                enfiler(f, g->tab_sommet[i]);
                verif= conditionFin(g->tab_sommet[i], puit);
                g->tab_sommet[i]->marque=1;
                g->tab_sommet[i]->pred=temp->position;
            }
        }
    }
    return g;
}

void fordFulkerson(Graphe* g)
{
    int finDeParcours=0;
    int flotMax=0;
    while(finDeParcours==0)//variable qui sera passé en pointeur du BFS, si le BFS ne trouve pas le puit alors fin
    {
        g= BFS(g);
        flotMax=rechercheFlotMax(g, recherche(g, 'O'));
        g= MaJFlotGraphe(g, recherche(g, 'O'), flotMax);
    }
}