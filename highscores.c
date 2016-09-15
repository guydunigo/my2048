#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "highscores.h"

int chargerHighscores(int highscores[NB_HIGHSCORES])
{
    FILE* fichier = NULL;
    char ligneFichier[10] = {0}, i = 0, *endptr;

    //On teste si le fichier existe sinon il est créé et si il est inscriptible.
    fichier = fopen("highscores.txt", "a+");
    if (fichier == NULL)
    {
        return 0;
    }
    fclose(fichier);

    //On l'ouvre pour de vrai.
    fichier = fopen("highscores.txt", "r");
    if (fichier == NULL)
    {
        return 0;
    }
    for (i = 0 ; i < NB_HIGHSCORES ; i++)
    {
        fgets(ligneFichier, 10, fichier);
        highscores[i] = strtol(ligneFichier, &endptr, 10);
    }

    fclose(fichier);
    return 1;
}

int sauvegarderHighscores(int highscores[NB_HIGHSCORES])
{
    FILE* fichier = NULL;
    char ligneFichier[10] = {0}, i = 0;

    fichier = fopen("highscores.txt", "w");
    if (fichier == NULL)
        return 0;

    for (i=0 ; i<NB_HIGHSCORES ; i++)
    {
        fprintf(fichier, "%hhd\n", highscores[i]);
    }

    fclose(fichier);
    return 1;
}

int scoreToHiscores(int highscores[NB_HIGHSCORES], int score)
{
    char i = 0, j = 0;
    if (score >= highscores[0])
    {
        for(i=NB_HIGHSCORES ; i>0 ; i--)
        {
            highscores[i]=highscores[i-1];
        }
        highscores[0]=score;
        return 2;
    }
    else if (score >= highscores[NB_HIGHSCORES-1])
    {
        for(i=0 ; score < highscores[i] ; i++);

        for(j = NB_HIGHSCORES ; j > i ; j--)
        {
            highscores[j]=highscores[j-1];
        }
        highscores[i] = score;
        return 1;
    }
    else
        return 0;
}
