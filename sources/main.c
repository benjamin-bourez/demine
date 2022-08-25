/*
** EPITECH PROJECT, 2022
** démineur
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char JEU[10][10];//grille de jeu 
int i,j;//i les lignes, j les colonnes
char MINES[10][10];//la grille avec les mines
int N;//Nombre de mines autour

////////////////////////////////////////
// FONCTION AFFICHER LA GRILLE DE JEU //
////////////////////////////////////////
void AfficheJeu()
{
     printf("   | 1  2  3  4  5  6  7  8  9  10\n");
     printf("___|______________________________\n");
     for(i=0;i<10;i++) {
        if(i<9)
            printf(" %d | ", (i+1));
        else
            printf("%d | ", (i+1));
        for(j=0;j<10;j++) {                
            printf("%c  ",JEU[i][j]);
        }
        printf("\n");
    }
}

/////////////////////////////////////////////
// FONCTION CALCULER LE NB DE MINES AUTOUR //
/////////////////////////////////////////////
int NbMinesAutour()
{
    N=0;
    if ((i - 1) > -1 && (j - 1) > -1 && MINES[i - 1][j - 1] == 'M')
        N++;
    if ((i - 1) > -1 && MINES[i - 1][j] == 'M')
        N++;
    if ((i - 1) > -1 && (j + 1) < 10 && MINES[i - 1][j + 1] == 'M')
        N++;
    if ((j - 1) > -1 && MINES[i][j - 1] == 'M')
        N++;
    if ((j + 1) < 10 && MINES[i][j + 1] == 'M')
        N++;
    if ((i + 1) < 10 && (j - 1) > -1 && MINES[i + 1][j - 1] == 'M')
        N++;
    if ((i + 1) < 10 && MINES[i + 1][j] == 'M')
        N++;
    if ((i + 1) < 10  && (j + 1) < 10 && MINES[i + 1][j + 1] == 'M')
        N++;
    return(N);
    }               

void discoveur()
{
    int savei = i;
    int savej = j;

    NbMinesAutour();
    if (N != 0) {
        JEU[i][j]= N + 48;
        return;
    } else {
        if (MINES[i][j] == 'M')
            return;
        JEU[i][j]='0';
        i -= 1;
        if (i > -1) {
            j -= 1;
            if (j > -1 && JEU[i][j] == '-')
                discoveur();
            j += 1;
            if (JEU[i][j] == '-')
                discoveur();
            j += 1;
            if (j < 10 && JEU[i][j] == '-')
                discoveur();
        }
        i += 1;
        j = savej - 1;
        if (j > -1 && JEU[i][j] == '-')
                discoveur();
        j = savej + 1;
        if (j < 10 && JEU[i][j] == '-')
                discoveur();
        i += 1;
        if (i < 10) {
            j = savej - 1;
            if (j > -1 && JEU[i][j] == '-')
                discoveur();
            j += 1;
            if (JEU[i][j] == '-')
                discoveur();
            j += 1;
            if (j < 10 && JEU[i][j] == '-')
                discoveur();
        }
    }
    i = savei;
    j = savej;
}

int check_win(int NbMines)
{
    int compte = 0;

    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
            if (JEU[x][y] == '-' || JEU[x][y] == 'D')
                compte += 1;
    if (compte == NbMines)
        return 1;
    return 0;
}

int main()
{
    int NbMines;//le nombre de mines choisi par le joueur
    int CompteMines;//compteur de mines
    int choix;//le choix effectué par le joueur pour découvrir ou placer un drapeau
    srand(time(NULL));       
    //Afficher le début du jeu
    printf(" ________________________________\n");
    printf("|                                |\n");
    printf("|        Jeu du demineur         |\n");
    printf("|________________________________|\n\n");
    //initialisation des deux grilles
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++) {
            JEU[i][j]=' ';//' 'implique case cachée
            MINES[i][j]='0';
        }           
    }
    //demander à l'utilisateur de choisir un nombre de mines
    do {
        printf("\nCombien de mines voulez-vous ?\n\n");
        scanf("%d",&NbMines);
    }
    while(NbMines>=30);
    printf("D'accord, vous avez choisi de jouer avec %d mines\n\n",NbMines);
    //////////////////////////////
    // Initialisation des mines //
    //////////////////////////////
    for (CompteMines=0;CompteMines<NbMines;CompteMines++) {  
        i=rand()%10;//on choisit la ligne de manière aléatoire
        j=rand()%10;//on choisit la colonne de manière aléatoire
        if(MINES[i][j]=='0') {//On vérifie que la case est libre
            MINES[i][j]='M';//on place un M pour indiquer qu'il y a une mine
        } else {
            CompteMines--;//Sinon, il y a déjà un M et il faut faire un tour de plus
        }
    }
    //Pour vérifier on affiche la grille des mines
    printf("Voici la grille des mines :\n");
    for(i=0;i<10;i++) {
        for(j=0;j<10;j++) {
            printf("%c  ",MINES[i][j]);
        }
        printf("\n");
    }
    ////////////////////////////
    // Démarrage de la partie //
    ////////////////////////////
    //On affiche le jeu au joueur
    printf("\n\nVoici votre grille : A vous de jouer !\n\n");
    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
    printf("___|______________________________\n");
    for(i=0;i<10;i++) {
        if(i<9)
            printf(" %d | ",i+1);
        else
            printf("%d | ",i+1);
        for(j=0;j<10;j++) {
            JEU[i][j]='-';//'-'implique case cachée
            printf("%c  ",JEU[i][j]);
        }
        printf("\n");
    }
    //On demande au joueur de choisir une case
    //la case est définie par sa ligne i et sa colonne j
    while (check_win(NbMines) != 1) {
        printf("\n\nVeuillez entrer la case choisie (numero de ligne [espace] numero de colonne):\t");
        scanf("%d %d",&i,&j);
        printf("Vous avez choisi la case (%d,%d).\n Que voulez-vous faire ?\n",i,j);
        i=i-1;
        j=j-1;
        // Demander au joueur ce qu'il veut faire
        printf("\t1. Decouvrir une case\n");
        printf("\t2. Placer un drapeau");
        do {
            printf("\t\tVotre choix : ");
            scanf("%d",&choix);
        } while (choix<0 || choix>2);
        // Choix : dévoiler une case ou placer un drapeau
        switch (choix) {
            case 1 : //fonction devoile mines autour
                if(MINES[i][j]=='M') {
                    printf("Vous avez perdu !!!\n\n");
                    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
                    printf("___|______________________________\n");
                    for(i=0;i<10;i++) {
                        if(i<9)
                            printf(" %d | ",i+1);
                        else
                            printf("%d | ",i+1);
                        for(j=0;j<10;j++)                
                            printf("%c  ",MINES[i][j]);
                        printf("\n");
                    }
                    exit(0);
                }
                NbMinesAutour();
                if (N!=0) {//Il y a des mines autour
                    JEU[i][j]= N + 48;
                } else {//Il n'y a pas de mines autour
                    JEU[i][j]='0';
                    discoveur();
                }
                break;
            case 2 :
                if (JEU[i][j] == '-')
                    JEU[i][j]='D';
                break;
        }
    //AFFICHER LA GRILLE
    AfficheJeu();
    }
    printf("\n\n\t\tBravo vous avez gagné !\n");
    return 0;
}