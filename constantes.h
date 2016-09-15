/* inclusion guard */
#ifndef __CONSTANTES_H__
#define __CONSTANTES_H__

#ifndef __arm__
#define TAILLE_BLOC		64
#define HAUTEUR_BANDE_SCORE	75
#endif

#ifdef __arm__
#define TAILLE_BLOC		32
#define HAUTEUR_BANDE_SCORE	25
#endif

#define NB_BLOCS_LARGEUR	4
#define NB_BLOCS_HAUTEUR	4
#define LARGEUR_FENETRE		TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE		TAILLE_BLOC * NB_BLOCS_HAUTEUR + HAUTEUR_BANDE_SCORE
#define NOMBRE			20
#define POLICE			"Arial.TTF"
#define NB_HIGHSCORES		10

enum {HAUT, BAS, GAUCHE, DROITE};

#endif /* __CONSTANTES_H__ */
