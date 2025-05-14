#include "header.h"



int initialiser_perso(Jeu *jeu) {
   
    jeu->background = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/backkk.png");
    jeu->button_single = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/single.png");
    jeu->button_multi = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/multi.png");
    jeu->button_left = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/cap2.png");
    jeu->button_right = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/cap3.png");
       jeu->alternate_sprites[0] = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/j2.png");
    jeu->alternate_sprites[1] = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/j3.png");
    jeu->current_alternate_sprite = 0; 
         jeu->button_custom = IMG_Load("ressource/button.png");
    jeu->player_sprites[0] = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/v1.png");  
 jeu->player_sprites[1] = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/v2.png");  
    jeu->player_sprites[2] = IMG_Load("/home/hiba/Desktop/aa/tach1/ressource/v3.png");  
    jeu->current_player_sprite = 0;  

    return 1;
}







void afficher_menu(Jeu *jeu) {
    SDL_Rect pos_single = {
        (SCREEN_WIDTH - jeu->button_single->w) / 2,
        (SCREEN_HEIGHT / 2) - jeu->button_single->h - 10,
        jeu->button_single->w,
        jeu->button_single->h
    };
    
    SDL_Rect pos_multi = {
        (SCREEN_WIDTH - jeu->button_multi->w) / 2,
        (SCREEN_HEIGHT / 2) + 10,
        jeu->button_multi->w,
        jeu->button_multi->h
    };

    SDL_BlitSurface(jeu->background, NULL, jeu->screen, NULL);
    SDL_BlitSurface(jeu->button_single, NULL, jeu->screen, &pos_single);
    SDL_BlitSurface(jeu->button_multi, NULL, jeu->screen, &pos_multi);
}

void afficher_joueur(Jeu *jeu) {
    SDL_BlitSurface(jeu->background, NULL, jeu->screen, NULL);

    // Déterminer quel sprite utiliser
    SDL_Surface *current_sprite = jeu->show_alternate_sprites ? 
                                  jeu->j2_sprite : 
                                  jeu->player_sprites[jeu->current_player_sprite];

    // Positionner le sprite central
    SDL_Rect pos_sprite = {
        (SCREEN_WIDTH - current_sprite->w) / 2,
        (SCREEN_HEIGHT - current_sprite->h) / 2,
        current_sprite->w,
        current_sprite->h
    };
    
    // Afficher le sprite principal
    SDL_BlitSurface(current_sprite, NULL, jeu->screen, &pos_sprite);

    // Calcul des positions des flèches
    SDL_Rect pos_left = {
        pos_sprite.x - jeu->button_left->w - 20, // 20px à gauche du sprite
        pos_sprite.y + (pos_sprite.h - jeu->button_left->h) / 2,
        jeu->button_left->w,
        jeu->button_left->h
    };

    SDL_Rect pos_right = {
        pos_sprite.x + pos_sprite.w + 20, // 20px à droite du sprite
        pos_left.y, // Même hauteur que la flèche gauche
        jeu->button_right->w,
        jeu->button_right->h
    };

    // Afficher les éléments
    SDL_BlitSurface(jeu->button_left, NULL, jeu->screen, &pos_left);
    SDL_BlitSurface(jeu->button_right, NULL, jeu->screen, &pos_right);

    // Bouton custom
    SDL_Rect pos_custom_button = {
        SCREEN_WIDTH - jeu->button_custom->w - 20,
        SCREEN_HEIGHT - jeu->button_custom->h - 20,
        jeu->button_custom->w,
        jeu->button_custom->h
    };
    SDL_BlitSurface(jeu->button_custom, NULL, jeu->screen, &pos_custom_button);
}




void changer_sprite_joueur(Jeu *jeu, int step) {
    
    jeu->current_player_sprite = (jeu->current_player_sprite + step + 3) % 3;
}

