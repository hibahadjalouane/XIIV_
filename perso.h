#ifndef PERSO_H 
#define PERSO_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


#define SCORE_PER_MOVE 1 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCORE_SIZE 24
#define IMG_WIDTH 128
#define IMG_HEIGHT 128
#define WALK_SPEED 4
#define RUN_SPEED 8
#define GRAVITY 1.5
#define JUMP_SPEED -22
#define WALK_FRAMES 6
#define RUN_FRAMES 8
#define JUMP_FRAMES 4
#define ATTACK_FRAMES 6
#define REST_FRAMES 6
/**
* @file perso.h
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for background scrollilng
*
*/






/**
 * @enum Action
 * @brief Defines different types of actions for the game.
 */
typedef enum {
    ADD_SCORE,
    RESET_SCORE,
    LOSE_LIFE,
    CHECK_ONLY

} Action;

/**
 * @file main.c
 * @brief Testing Program.
 * @author C Team
 * @version 0.1
 * @date Apr 01, 2015
 *
 * Testing program for background scrolling
 *
 */





/**
 * @enum PersoState
 * @brief Enumeration for character (Perso) states.
 */
typedef enum {
    REST,
    WALK,
    RUN,
    JUMP,
    ATTACK
} PersoState;






/**
 * @struct Jeu
 * @brief Structure contenant tous les éléments du jeu.
 */
typedef struct {
    SDL_Surface *screen; 
    SDL_Surface *background, *rest_img, *walk_img, *run_img, *jump_img, *attack_img, *heart_img;
    TTF_Font *font; 
    SDL_Color text_color;
    SDL_Rect char_pos; 
    SDL_Rect frame;    
    int score;        
    int lives;         
    float y_speed;     
    int on_ground;    
    int running;     
    PersoState state;  
} Jeu;


int initialiser_perso(Jeu *jeu);
void animation(Jeu *jeu, int frames, int dureeParFrame);
void deplacer_perso(Jeu *jeu, const Uint8 *keys);
void saut(Jeu *jeu);
void afficher_jeu(Jeu *jeu);
void score_vies(Jeu *jeu, Action action, int valeur);
#endif
