/* inclusion guard */
#ifndef __FICHIERS_H__
#define __FICHIERS_H__

#include "constantes.h"

int chargerHighscores(int highscores[NB_HIGHSCORES]);

int sauvegarderHighscores(int highscores[NB_HIGHSCORES]);

int scoreToHiscores(int highscores[NB_HIGHSCORES], int score);//Retourne 2 si 'score' est le meilleur, 1 si il fait partie de la liste, et 0 sinon.

#endif /* __FICHIERS_H__ */
