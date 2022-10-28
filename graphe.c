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
            graphe->mat_flot[i][j]=0;
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
    printf("\t Matrice de capacite\n");
    for(int i=0;i<graphe->ordre;i++)
    {
        printf("%c ",graphe->tab_sommet[i]->lettre);//on affiche le noms des sommets
        for(int j=0;j<graphe->ordre;j++)
        {
            printf("%d\t",graphe->mat_capacite[i][j]);
        }
        printf("\n");
    }
    printf("\t Matrice de flot\n");
    for(int i=0;i<graphe->ordre;i++)
    {
        printf("%c ",graphe->tab_sommet[i]->lettre);//on affiche le noms des sommets
        for(int j=0;j<graphe->ordre;j++)
        {
            printf("%d\t",graphe->mat_flot[i][j]);
        }
        printf("\n");
    }
}
//on fait un bfs

t_id_sommet* rechercheSource(Graphe* g)
{
    int verif;
    int i, j;
    for(i=0; i<g->ordre; i++)
    {
        verif=1;
        for(j=0; j<g->ordre; j++)
        {
            if(g->mat_capacite[j][i]!=0)
            {
                verif=0;
            }
        }
        if(verif==1)
        {
            break;
        }
    }
    if(verif==0)
    {
        printf("Erreur, il n'y a pas de source dans le graphe\n");
        exit(1);
    }
    return g->tab_sommet[i];
}

t_id_sommet* recherchePuit(Graphe* g)
{

    int verif, i, j;
    for(i=0; i<g->ordre; i++)
    {
        verif=1;
        for(j=0; j<g->ordre; j++)
        {
            if(g->mat_capacite[i][j]!=0)
            {
                verif=0;
            }
            if(verif==1)
            {
                break;
            }
        }
    }
    if(verif==0)
    {
        printf("Erreur, il n'y a pas de puit dans le graphe\n");
        exit(1);
    }
    return g->tab_sommet[i-1];//i-1 car on fait une itération en plus
}

int rechercheFlotMax(Graphe* g, t_id_sommet* depart)//depart qu'on retrouve en utilisant recherche
{
    int flotMax=100;
    int sommetActu=depart->position;
    int sommetPred=-1;
    int tempFlotRestant=0;
    while(g->tab_sommet[sommetActu]->pred!=-1)
    {
        printf("sommet %c : ", g->tab_sommet[sommetActu]->lettre);
        sommetPred=g->tab_sommet[sommetActu]->pred;
        tempFlotRestant=g->mat_capacite[sommetPred][sommetActu]-g->mat_flot[sommetPred][sommetActu];
        printf("%d -> ", tempFlotRestant);
        if(tempFlotRestant<flotMax)
        {
           flotMax=tempFlotRestant;
        }
        sommetActu=sommetPred;
    }
    printf("sommet O");
    printf("\n");
    return flotMax;
}


Graphe* MaJFlotGraphe(Graphe* g, t_id_sommet* depart, int flotMax)
{
    int sommetActu=depart->position;
    int sommetPred=-1;
    while(g->tab_sommet[sommetActu]->pred!=-1)
    {
        sommetPred=g->tab_sommet[sommetActu]->pred;
        g->mat_flot[sommetPred][sommetActu]+=flotMax;
        sommetActu=sommetPred;
    }
    return g;
}

Graphe* BFS(Graphe* g, int* verifFin)
{
    printf("BFS en cours\n");
    t_id_sommet* place, *temp;
    temp= recherchePuit(g);
    char puit=temp->lettre;
    int verif=0;
    for(int i=0; i<g->ordre; i++)
    {
        g->tab_sommet[i]->marque=0;
        g->tab_sommet[i]->pred=-1;
    }

    place= rechercheSource(g);

    t_file* f=creation();

    f=enfiler(f, g->tab_sommet[place->position]);
    //afficherListe(f);

    g->tab_sommet[place->position]->marque=1;
    while(verif==0 && !estVide(f))//rajouter si la liste est vide aussi
    {
        f=defiler(f, &temp);
        //printf("Apres defilement : \n");
        //afficherListe(f);
        for(int i=0; i<g->ordre; i++)
        {
            if(g->mat_capacite[temp->position][i]!=0 && g->mat_capacite[temp->position][i]!=g->mat_flot[temp->position][i] && g->tab_sommet[i]->marque==0)//si le sommet n'est pas marqué et qu'il existe un lien entre les 2 sommets et que l'arrete n'est pas saturé
            {
                enfiler(f, g->tab_sommet[i]);
                if(g->tab_sommet[i]== recherchePuit(g))//on le fait que si verif est tjr égale à 0 sinon on risque d'overwrite la valeur
                {
                    printf("puit trouve\n");
                    verif=1;
                }
                g->tab_sommet[i]->marque=1;
                g->tab_sommet[i]->pred=temp->position;
            }
        }
        //printf("Apres enfilement : \n");
        //afficherListe(f);
        //printf("verif final = %d\n", verif);
    }
    if(verif==0)
    {
        printf("puit non trouve\n");
    }
    *verifFin=verif;
    return g;
}

Graphe* fordFulkerson(Graphe* g)
{
    int finDeParcours=1;
    int flotMax=0;
    while(finDeParcours==1)//variable qui sera passé en pointeur du BFS, si le BFS ne trouve pas le puit alors fin
    {
        g= BFS(g, &finDeParcours);
        flotMax=rechercheFlotMax(g, recherchePuit(g));
        printf("flot max = %d\n", flotMax);
        g= MaJFlotGraphe(g, recherchePuit(g), flotMax);
        //afficher_graphe(g);

    }
    return g;
}

void calculFlotMax(Graphe* g, t_id_sommet* source)
{
    int flotMax=0;
    for(int i=0; i<g->ordre; i++)
    {
        for(int j=0; j<g->ordre; j++)
        {
            printf("%d\t", g->mat_flot[i][j]);
            if(g->tab_sommet[i]==source)
            {
                flotMax+=g->mat_flot[i][j];
            }
        }
        printf("\n");
    }

    printf("flot max : %d\n", flotMax);
}