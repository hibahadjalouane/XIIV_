#ifndef HEADER_Hs
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>  // Added this line
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
typedef enum {
    MENU_SCREEN,
    SINGLE_PLAYER_SCREEN,
    MULTI_PLAYER_SCREEN
} GameState;

typedef struct {
    SDL_Surface *screen; 
    SDL_Surface *background;
    TTF_Font *font; 
    SDL_Color text_color;  
    SDL_Surface *button_single;  // Bouton Single Player
    SDL_Surface *button_multi;
SDL_Surface *button_left;    // Left arrow
    SDL_Surface *button_right; 
SDL_Surface *j2_sprite;

 SDL_Surface *button_custom;
SDL_Surface *player_sprites[3];
    GameState current_state;
int current_player_sprite; 
 int show_alternate_sprites;
} Jeu;


int initialiser_perso(Jeu *jeu);
void afficher_menu(Jeu *jeu);
void afficher_joueur(Jeu *jeu);
void changer_sprite_joueur(Jeu *jeu, int step);


#endif
