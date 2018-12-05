/*
narrow.c
principe du retricissement de la map
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "player.h"
#include "obstacles.h"
#include "constantes.h"
#include "narrow.h"

/*
PRINCIPE
En deux temps :
    Affichage
Regarde la pos x du rect renvoy�, et cr�� x lignes de tous les cot�s
    Fonctionnement
Si le joueur n'est pas en collision totale avec le rect renvoy�, il meurt
*/

// Prend en parametre la zone viable.
// arg : 0 si on reset
// arg : 1 si on augmente la zone
// arg : -1 si on retrecie la zone
void updateNarrow(SDL_Rect *zone, int arg)
{
    switch(arg)
    {
    case -1:
        if (zone->x < LIMIT_NARROW) {
            zone->x++;
            zone->y++;
            zone->h-=2;
            zone->w-=2;
        }
        break;
    case 0:
        zone->x = 0;
        zone->y = 0;
        zone->h = HEIGHT_GAME;
        zone->w = WIDTH_GAME;
        break;
    case 1:
        zone->x--;
        zone->y--;
        zone->h+=2;
        zone->w+=2;
        break;
    default:
        break;
    }
}

// Regarde s'il faut tuer le perso
bool deadlyNarrow(Player *p, SDL_Rect *zone)
{
    int i = 0;
    // Coin superieur gauche
    if (p->hitbox.x > zone->x && zone->x + zone->w > p->hitbox.x && p->hitbox.y > zone->y && zone->y + zone->h > p->hitbox.y) i++;
    // Coin superieur droit
    if (p->hitbox.x + p->hitbox.w > zone->x && zone->x + zone->w > p->hitbox.x + p->hitbox.w && p->hitbox.y > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;
    // Coin inferieur gauche
    if (p->hitbox.x > zone->x && zone->x + zone->w > p->hitbox.x && p->hitbox.y + p->hitbox.h > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;
    // Coin inferieur droit
    if (p->hitbox.x + p->hitbox.w > zone->x && zone->x + zone->w > p->hitbox.x + p->hitbox.w && p->hitbox.y + p->hitbox.h > zone->y && zone->y + zone->h > p->hitbox.y + p->hitbox.h) i++;

    if (i == 4) return false;
    else return true;
}

