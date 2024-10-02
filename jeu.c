#include <SDL/SDL.h>
#include <SDL/SDL_image.h> //Pour la grille.
#include <SDL/SDL_ttf.h>
#include <math.h> // Pour les puissances de deux.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pour l'aléatoire.

#include "constantes.h"
#include "jeu.h"

int jouer(SDL_Surface *ecran) {
    SDL_Surface *grille = NULL, *texte = NULL;
    SDL_Surface *nombre[NOMBRE] = {NULL};
    SDL_Rect positionGrille, position, positionTexte;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleur = {0, 0, 0, 0};

    int continuer = 1, i = 0, j = 0, nb = 1, nbChiffres = 0, taille = 0,
        score = 0, x = 0, y = 0; // + casesVides
    int casesVides[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR] = {0},
                                      cases[NB_BLOCS_LARGEUR]
                                           [NB_BLOCS_HAUTEUR] = {0};
    char puissanceDeux[100];

    // Chargement des Sprites
#ifndef __arm__
    grille = IMG_Load("images/grille.png");
#endif
#ifdef __arm__
    grille = IMG_Load("images/petitegrille.png");
#endif

    positionGrille.x = 0;
    positionGrille.y = HAUTEUR_BANDE_SCORE;

    // Génération des cases de nombres + couleur
    for (i = 0; i < NOMBRE; i++) {
        // On augmente d'une puissance de deux.
        nb *= 2;

        // Changement de la couleur du texte
        if (i == 0 || i == 1) {
            couleur.r = 119;
            couleur.g = 110;
            couleur.b = 101;
        } else {
            couleur.r = 249;
            couleur.g = 246;
            couleur.b = 242;
        }
        // return 0;

        // Mise à jour du texte.
        nbChiffres = nombreChiffres(nb);
        taille = TAILLE_BLOC / nbChiffres * 0.95;
        {
            police = TTF_OpenFont(POLICE, taille);
            sprintf(puissanceDeux, "%d", nb);
            texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
            TTF_CloseFont(police);
        }
        position.x = TAILLE_BLOC / 2 - texte->w / 2;
        position.y = TAILLE_BLOC / 2 - texte->h / 2;

        // Changement de la couleur du fond.
        switch (i) {
        case 0:
            couleur.r = 255 - 238;
            couleur.g = 255 - 228;
            couleur.b = 255 - 218;
            break;
        case 1:
            couleur.r = 255 - 237;
            couleur.g = 255 - 224;
            couleur.b = 255 - 200;
            break;
        case 2:
            couleur.r = 255 - 242;
            couleur.g = 255 - 177;
            couleur.b = 255 - 121;
            break;
        case 3:
            couleur.r = 255 - 245;
            couleur.g = 255 - 149;
            couleur.b = 255 - 99;
            break;
        case 4:
            couleur.r = 255 - 246;
            couleur.g = 255 - 124;
            couleur.b = 255 - 95;
            break;
        case 5:
            couleur.r = 255 - 246;
            couleur.g = 255 - 94;
            couleur.b = 255 - 59;
            break;
        case 6:
            couleur.r = 255 - 237;
            couleur.g = 255 - 207;
            couleur.b = 255 - 114;
            break;
        default:
            couleur.b = (255 / NOMBRE) * i;
            couleur.g = (255 / NOMBRE) * i;
            couleur.r = (255 / NOMBRE) * i;
        }

        // Placement du texte dans la case.
        nombre[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_BLOC - 1,
                                         TAILLE_BLOC - 1, 32, 0, 0, 0, 0);
        SDL_FillRect(nombre[i], NULL,
                     SDL_MapRGB(nombre[i]->format, 255 - couleur.r,
                                255 - couleur.g, 255 - couleur.b));
        SDL_BlitSurface(texte, NULL, nombre[i], &position);
        SDL_FreeSurface(texte);
    }
    SDL_Flip(ecran);

    // Configuration du texte affichant le score.
    couleur.r = 119;
    couleur.g = 110;
    couleur.b = 101;
#ifndef __arm__
    taille = TAILLE_BLOC * 0.95;
#endif
#ifdef __arm__
    taille = TAILLE_BLOC * 0.85;
#endif
    police = TTF_OpenFont(POLICE, taille);
    // Calcul hauteur texte en générant un faux score.
    {
        sprintf(puissanceDeux, "%d", score);
        texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
        positionTexte.x = 10;
        positionTexte.y = HAUTEUR_BANDE_SCORE / 2 - texte->h / 2;
        SDL_FreeSurface(texte);
    }

    placerNbAlea(cases, casesVides);
    placerNbAlea(cases, casesVides);
    /*    cases[0][3] = 14;
        cases[0][2] = 13;
        cases[0][1] = 12;
        cases[0][0] = 11;
        cases[1][3] = 7;
        cases[1][2] = 8;
        cases[1][1] = 9;
        cases[1][0] = 10;
        cases[2][3] = 6;
        cases[2][2] = 5;
        cases[2][1] = 4;
        cases[2][0] = 3;
        cases[3][0] = 3;
        cases[3][1] = 1;
        cases[3][2] = 1;*/

    // Boucle Principale.
    while (continuer) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_UP:
                changerGravite(&score, cases, HAUT);
                break;
            case SDLK_DOWN:
                changerGravite(&score, cases, BAS);
                break;
            case SDLK_LEFT:
                changerGravite(&score, cases, GAUCHE);
                break;
            case SDLK_RIGHT:
                changerGravite(&score, cases, DROITE);
                break;
            default:
                break;
            }
            // Ajout d'une case (2 ou 4)
            if (event.key.keysym.sym == SDLK_UP ||
                event.key.keysym.sym == SDLK_DOWN ||
                event.key.keysym.sym == SDLK_LEFT ||
                event.key.keysym.sym == SDLK_RIGHT) {
                if (detecterCasesVides(cases, casesVides) ==
                    0) // Si aucune case n'a pu être bougée par manque de place.
                    continuer = 0;
                else
                    placerNbAlea(cases, casesVides);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            x = event.button.x;
            y = event.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            x -= event.button.x;
            y -= event.button.y;
            if (x > 0 && abs(x) > abs(y))
                changerGravite(&score, cases, GAUCHE);
            else if (x < 0 && abs(x) > abs(y))
                changerGravite(&score, cases, DROITE);
            else if (y > 0 && abs(x) < abs(y))
                changerGravite(&score, cases, HAUT);
            else if (y < 0 && abs(x) < abs(y))
                changerGravite(&score, cases, BAS);
            else
                break;
            // Ajout d'une case (2 ou 4)
            if (detecterCasesVides(cases, casesVides) ==
                0) // Si aucune case n'a pu être bougée par manque de place.
                continuer = 0;
            else
                placerNbAlea(cases, casesVides);
            break;
        }

        // Effacement de l'écran et nettoyage de la grille.
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 204, 192, 179));

        // Placement du score.
        sprintf(puissanceDeux, "%d", score);
        {
            texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
            positionTexte.x = LARGEUR_FENETRE / 2 - texte->w / 2;
            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
            SDL_FreeSurface(texte);
        }

        // Placement des Cases.
        for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
                nb = cases[i][j] - 1;
                if (nb != -1) {
                    position.x = i * TAILLE_BLOC;
                    position.y = j * TAILLE_BLOC + HAUTEUR_BANDE_SCORE;

                    SDL_BlitSurface(nombre[nb], NULL, ecran, &position);
                }
            }
        }

        SDL_BlitSurface(grille, NULL, ecran, &positionGrille);
        SDL_Flip(ecran);
    }

    // Nettoyage des surfaces.
    SDL_FreeSurface(grille);
    // SDL_FreeSurface(texte);
    for (i = 0; i < NOMBRE; i++)
        SDL_FreeSurface(nombre[i]);
    TTF_CloseFont(police);

    return score;
}

void changerGravite(int *score, int cases[][NB_BLOCS_HAUTEUR], int sens) {
    int i = 0, j = 0;
    int retourDeplacer = 0;

    switch (sens) {
    case HAUT:
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {
                switch (j) {
                case 1:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if (retourDeplacer == 0)
                        retourDeplacer =
                            deplacerCases(&cases[i][j - 1], &cases[i][j - 2]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    if (retourDeplacer == 0) {
                        retourDeplacer =
                            deplacerCases(&cases[i][j - 1], &cases[i][j - 2]);
                        if (retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[i][j - 2],
                                                           &cases[i][j - 3]);
                        if (retourDeplacer > 0)
                            *score += pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case BAS:
        for (i = 0; i < 4; i++) {
            for (j = 2; j >= 0; j--) {
                switch (3 - j) {
                case 1:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if (retourDeplacer == 0)
                        retourDeplacer =
                            deplacerCases(&cases[i][j + 1], &cases[i][j + 2]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer =
                        deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    if (retourDeplacer == 0) {
                        retourDeplacer =
                            deplacerCases(&cases[i][j + 1], &cases[i][j + 2]);
                        if (retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[i][j + 2],
                                                           &cases[i][j + 3]);
                        if (retourDeplacer > 0)
                            *score += pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case GAUCHE:
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {
                switch (j) {
                case 1:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if (retourDeplacer == 0)
                        retourDeplacer =
                            deplacerCases(&cases[j - 1][i], &cases[j - 2][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    if (retourDeplacer == 0) {
                        retourDeplacer =
                            deplacerCases(&cases[j - 1][i], &cases[j - 2][i]);
                        if (retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[j - 2][i],
                                                           &cases[j - 3][i]);
                        if (retourDeplacer > 0)
                            *score += pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case DROITE:
        for (i = 0; i < 4; i++) {
            for (j = 2; j >= 0; j--) {
                switch (3 - j) {
                case 1:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if (retourDeplacer == 0)
                        retourDeplacer =
                            deplacerCases(&cases[j + 1][i], &cases[j + 2][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer =
                        deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if (retourDeplacer > 0)
                        *score += pow(2, retourDeplacer);
                    if (retourDeplacer == 0) {
                        retourDeplacer =
                            deplacerCases(&cases[j + 1][i], &cases[j + 2][i]);
                        if (retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[j + 2][i],
                                                           &cases[j + 3][i]);
                        if (retourDeplacer > 0)
                            *score += pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    }
}

int deplacerCases(int *premiereCase, int *secondeCase) {
    if (*secondeCase == 0) {
        *secondeCase = *premiereCase;
        *premiereCase = 0;
        return 0;
    } else if (*secondeCase == *premiereCase) {
        (*secondeCase)++;
        *premiereCase = 0;
        return *secondeCase;
    } else
        return -1;
}

int nombreChiffres(int nombre) {
    int nbChiffres = 0;

    if (nombre == 0) {
        nbChiffres = 1;
    } else {
        while (nombre != 0) {
            nbChiffres += 1;
            nombre /= 10;
        }
    }
    return nbChiffres;
}

void placerNbAlea(int cases[][NB_BLOCS_HAUTEUR],
                  int casesVides[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR]) {
    int nbCasesVides = 0, caseChoisie = 0, nombre = 0;
    srand(time(NULL));
    nombre = rand() % 30 + 1;
    if (nombre < 29)
        nombre = 1;
    else
        nombre = 2;
    nbCasesVides = detecterCasesVides(cases, casesVides);
    caseChoisie = casesVides[rand() % nbCasesVides];
    if (cases[caseChoisie / 10][caseChoisie - (caseChoisie / 10) * 10] != 0) {
        exit(EXIT_FAILURE);
    }
    cases[caseChoisie / 10][caseChoisie - (caseChoisie / 10) * 10] = nombre;
}

int detecterCasesVides(int cases[][NB_BLOCS_HAUTEUR],
                       int casesVides[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR]) {
    int i = 0, j = 0, nbCasesVides = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (cases[i][j] == 0) {
                casesVides[nbCasesVides] = i * 10 + j;
                nbCasesVides++;
            }
        }
    }
    casesVides[nbCasesVides] = 0;

    return nbCasesVides;
}
