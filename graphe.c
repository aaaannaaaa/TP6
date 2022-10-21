//
// Created by joyen on 21/10/2022.
//

#include "graphe.h"
// creer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->id_sommet=(char*)malloc(ordre*sizeof(char)); //on crée un tableau rempli par tous nos sommets
    Newgraphe->mat_capacite=(int**)malloc(ordre*sizeof(int*)); //on crée la premiere ligne de la matrice de capacité
    Newgraphe->mat_flot=(int**)malloc(ordre*sizeof(int*));//on crée la premiere ligne de la matrice de flot
    for(int i=0; i<ordre; i++)
    {
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
        fscanf(ifs,"%c",&graphe->id_sommet[i]);//on rempli notre tableau de sommet par la valeur des sommets qu'on lit dans le fichier

    }
    graphe->ordre=ordre;
    printf("ordre %d", ordre);


    //on remplit la matrice de capa
    for(int i=0;i<ordre;i++)
    {
        for(int j=0;j<ordre;j++)
        {
            fscanf(ifs,"%d",&graphe->mat_capacite[i][j]);//on remplit la case
        }

        //on passe a la ligne suivante du fichier

    }



    return graphe;
}
void afficher_graphe(Graphe * graphe)
{
    printf("%d\n",graphe->ordre); //on affiche l'ordre
    printf("\n");
    for(int i=0;i<graphe->ordre;i++)
    {
        printf("%c ",graphe->id_sommet[i]);//on affiche le noms des sommets
        for(int j=0;j<graphe->ordre;j++)
        {
            printf("%d\n",graphe->mat_capacite[i][j]);

        }
        printf("ho\n");
    }
}
//on fait un bfs
//on crée un file