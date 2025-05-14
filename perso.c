#include "perso.h"
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string.h>

/**
 * @file perso.c
 * @brief Testing Program.
 * @author C Team
 * @version 0.1
 * @date Apr 01, 2015
 *
 * Testing program for background scrolling
 *
 */






/**
 * @brief Initialise les éléments du personnage et du jeu
 * @param[in,out] jeu Pointeur vers la structure Jeu à initialiser
 * @return 1 si l'initialisation réussit, 0 sinon
 *
 * Charge les images nécessaires et initialise les positions,
 * vitesses, états et paramètres du jeu.
 */
int initialiser_perso(Jeu *jeu) {
    jeu->background = IMG_Load("assets/pixel_art_large.png");
    jeu->rest_img = IMG_Load("Attack_2.png");
    jeu->walk_img = IMG_Load("Walk.png");
    jeu->run_img = IMG_Load("Run.png");
    jeu->jump_img = IMG_Load("Jump.png");
    jeu->attack_img = IMG_Load("Attack_1.png");
    jeu->heart_img = IMG_Load("/home/hiba/Desktop/aa/etape2/assets/coeur1.png");

    jeu->text_color = (SDL_Color){255, 255, 255};
    jeu->char_pos = (SDL_Rect){0, 400, IMG_WIDTH, IMG_HEIGHT};
    jeu->frame = (SDL_Rect){0, 0, IMG_WIDTH, IMG_HEIGHT};

    jeu->running = 1;
    jeu->y_speed = 0;
    jeu->on_ground = 1;
    jeu->score = 0;
    jeu->lives = 3;
    jeu->state = REST;

    return 1;
}

/**
 * @brief Gère l'animation du personnage
 * @param[in,out] jeu Pointeur vers la structure Jeu
 * @param[in] frames Nombre total de frames dans l'animation
 * @param[in] dureeParFrame Durée d'affichage de chaque frame (ms)
 *
 * Calcule la frame actuelle à afficher en fonction du temps écoulé
 * et met à jour la position x de la frame dans la structure Jeu.
 */
void animation(Jeu *jeu, int frames, int dureeParFrame) {
    int tempsEcoule = SDL_GetTicks();
    int nbIntervalles = tempsEcoule / dureeParFrame;
    int frame = nbIntervalles % frames;
    jeu->frame.x = frame * IMG_WIDTH;
}

/**
 * @brief Gère le déplacement du personnage
 * @param[in,out] jeu Pointeur vers la structure Jeu
 * @param[in] keys Tableau contenant l'état des touches du clavier
 *
 * Déplace le personnage à gauche ou à droite en fonction des touches pressées
 * et met à jour son état (RUN ou REST).
 */
void deplacer_perso(Jeu *jeu, const Uint8 *keys) {
    int vitesse = WALK_SPEED;
    if (keys[SDLK_LEFT]) {
        
        if (jeu->char_pos.x > 0) {
            jeu->char_pos.x -= vitesse;
        } else {
            jeu->char_pos.x = 0;
        }

        jeu->state = RUN;
    }
  
    else if (keys[SDLK_RIGHT]) {
        
        if (jeu->char_pos.x < SCREEN_WIDTH - IMG_WIDTH) {
            jeu->char_pos.x += vitesse;
        } else {
            jeu->char_pos.x = SCREEN_WIDTH - IMG_WIDTH;
        }

        jeu->state = RUN;
    }
    else if (jeu->on_ground) {
        jeu->state = REST;
    }
}




/**
 * @brief Gère la physique du saut et la gravité
 * @param[in,out] jeu Pointeur vers la structure Jeu
 *
 * Applique la gravité lorsque le personnage est en l'air,
 * met à jour sa position verticale et détecte l'atterrissage.
 */
void saut(Jeu *jeu) {
    if (!jeu->on_ground) {
        jeu->y_speed += GRAVITY;
        jeu->char_pos.y += jeu->y_speed;
        if (jeu->char_pos.y >= 400) {
            jeu->char_pos.y = 400;
            jeu->y_speed = 0;
            jeu->state = REST;
            jeu->on_ground = 1;
        }
    }
}
/**
 * @brief Affiche l'état actuel du jeu
 * @param[in,out] jeu Pointeur vers la structure Jeu
 *
 * Sélectionne le sprite approprié en fonction de l'état du personnage,
 * calcule l'animation et affiche tous les éléments à l'écran.
 */
void afficher_jeu(Jeu *jeu) {
    SDL_Surface *sprite = jeu->rest_img; 
    int frames = REST_FRAMES;

    if (jeu->state == REST) {
        sprite = jeu->rest_img;
        frames = REST_FRAMES;
    } else if (jeu->state == WALK) {
        sprite = jeu->walk_img;
        frames = WALK_FRAMES;
    } else if (jeu->state == RUN) {
        sprite = jeu->run_img;
        frames = RUN_FRAMES;
    } else if (jeu->state == JUMP) {
        sprite = jeu->jump_img;
        frames = JUMP_FRAMES;
    } else if (jeu->state == ATTACK) {
        sprite = jeu->attack_img;
        frames = ATTACK_FRAMES;
    }

    int tempsEcoule = SDL_GetTicks();
    int dureeParFrame = 100;
    int nbIntervalles = tempsEcoule / dureeParFrame;

    int frame = nbIntervalles % frames;
    jeu->frame.x = frame * IMG_WIDTH;

    SDL_FillRect(jeu->screen, NULL, SDL_MapRGB(jeu->screen->format, 0, 0, 0));
    SDL_BlitSurface(jeu->background, NULL, jeu->screen, NULL);
    SDL_BlitSurface(sprite, &jeu->frame, jeu->screen, &jeu->char_pos);
    score_vies(jeu, CHECK_ONLY, 0);
    SDL_UpdateRect(jeu->screen, 0, 0, 0, 0);
}
/**
 * @brief Gère le score et les vies du joueur
 * @param[in,out] jeu Pointeur vers la structure Jeu
 * @param[in] action Action à effectuer (ADD_SCORE, RESET_SCORE, LOSE_LIFE)
 * @param[in] valeur Valeur à utiliser pour l'action
 *
 * Modifie le score ou les vies en fonction de l'action demandée
 * et affiche les nouvelles valeurs à l'écran.
 */

void score_vies(Jeu *jeu, Action action, int valeur) {
    switch(action) {
        case ADD_SCORE:
            jeu->score += valeur; 
            break;
        case RESET_SCORE: 
            jeu->score = 0; 
            jeu->lives = 3;
            break;
        case LOSE_LIFE: 
            if(--jeu->lives <= 0) jeu->running = 0; 
            break;
        default: 
            break;
    }
    if (!jeu->font) {
        printf("Erreur: Police non chargée!\n");
        return;
    }

    char score_text[32];
    snprintf(score_text, sizeof(score_text), "Score: %d", jeu->score);
    SDL_Surface *text = TTF_RenderText_Solid(jeu->font, score_text, jeu->text_color);
    SDL_Rect pos = {SCREEN_WIDTH - 200, 20, 0, 0};
    SDL_BlitSurface(text, NULL, jeu->screen, &pos);
    SDL_FreeSurface(text);

    for(int i = 0; i < jeu->lives; i++) {
        SDL_Rect heart_pos = {
            .x = 20 + i * 50,
            .y = 20,
            .w = jeu->heart_img->w,
            .h = jeu->heart_img->h
        };
        SDL_BlitSurface(jeu->heart_img, NULL, jeu->screen, &heart_pos);
    }
}
