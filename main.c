#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "highscores.h"
#include "jeu.h"

int main() {
    SDL_Surface *ecran = NULL, *menu = NULL, *titre = NULL;
    SDL_Rect positionMenu, posTitre;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0, 0};

    int continuer = 1, score = 0, highscores[NB_HIGHSCORES] = {0};

    if (chargerHighscores(highscores) == 0)
        printf("Impossible de charger les scores\n");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32,
                             SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("My 2048", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    {
        police = TTF_OpenFont(POLICE, (LARGEUR_FENETRE - 5) / 6);

        titre = TTF_RenderText_Blended(police, "My 2048", couleurNoire);
        posTitre.x = 49;
        posTitre.y = 25;

        TTF_CloseFont(police);
    }

    {
        police = TTF_OpenFont(POLICE, (LARGEUR_FENETRE - 5) / 7);
        menu = TTF_RenderText_Blended(police, "1) Lancer le Jeu", couleurNoire);
        positionMenu.x = 0;
        positionMenu.y = 100;
        TTF_CloseFont(police);
    }

    SDL_Flip(ecran);

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
            case SDLK_KP1:
                score = jouer(ecran);
                scoreToHiscores(highscores, score);
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            score = jouer(ecran);
            scoreToHiscores(highscores, score);
            break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(titre, NULL, ecran, &posTitre);
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }
    sauvegarderHighscores(highscores);

    SDL_FreeSurface(menu);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(ecran);
    TTF_Quit();
    SDL_Quit();
}
