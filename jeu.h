/* inclusion guard */
#ifndef __JEU_H__
#define __JEU_H__

#include "constantes.h"

int jouer(SDL_Surface* ecran);// Retourne le score.

void changerGravite(int *score, int cases[][NB_BLOCS_HAUTEUR], int sens);

int deplacerCases(int* premiereCase, int* secondeCase);// Retourne 0 si la case a été déplacée, la puissance de deux si elle a été fusionnée et -1 sinon.

int nombreChiffres(int nombre);// Renvoie le nombre de chiffres qui composent le nombre en base 10.

void placerNbAlea(int cases[][4], int casesVides[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR]);

int detecterCasesVides(int cases[][4], int casesVides[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR]);// Remplie le tableau casesVides contenant les coordonnées des cases vides, il se termine pas un NULL.

#endif /* __JEU_H__ */
