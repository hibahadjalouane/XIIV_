
#include <SDL/SDL.h>       
#include <SDL/SDL_ttf.h>   
#include "perso.h"         
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
int main() {
    
   
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Jeu game ;
    game.font = TTF_OpenFont("assets/arial.ttf", SCORE_SIZE);
  
    game.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

   
    if (!initialiser_perso(&game)) {
        printf("Erreur d'initialisation du personnage\n");
        return 1;  
    }

   
    SDL_Event event;        
    Uint8 *keys;            

    while (game.running) {
        
        while (SDL_PollEvent(&event)) {
            
            if (event.type == SDL_QUIT) {
                game.running = 0;  
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                   
                    case SDLK_DOWN:
                        score_vies(&game, LOSE_LIFE, 0);
                        break;
                 
                    case SDLK_r:
                        score_vies(&game, RESET_SCORE, 0);
                        break;
                        
                   
                    case SDLK_SPACE:
                        if (game.on_ground) { 
                            game.y_speed = JUMP_SPEED;
                            game.on_ground = 0;  
                            game.state = JUMP;   
                        }
                        break;
                        
                    
                    case SDLK_a:
                        game.state = ATTACK;
                        break;
                }
            }
        }

        keys = SDL_GetKeyState(NULL);

       
        if (keys[SDLK_LEFT]) {
            
	if(game.char_pos.x > 0) {
    		game.char_pos.x = game.char_pos.x - WALK_SPEED;
	} else {
    		game.char_pos.x = 0;
	}
            game.state = RUN;              
            score_vies(&game, ADD_SCORE, 1);
        }
      
        else if (keys[SDLK_RIGHT]) {
	int positionMaxDroite = SCREEN_WIDTH - IMG_WIDTH;
	if(game.char_pos.x < positionMaxDroite) {
    		game.char_pos.x += WALK_SPEED;
	} else {
    		game.char_pos.x = positionMaxDroite;
	}
            game.state = RUN;              
            score_vies(&game, ADD_SCORE, 1);
        }
       
        else if (game.on_ground) {
            game.state = REST;  
        }

        deplacer_perso(&game, keys);  
        saut(&game);                 
        afficher_jeu(&game);         

       
        SDL_Delay(16);  
    }

    
  
    TTF_CloseFont(game.font);
    
    SDL_FreeSurface(game.background);
    
  
    SDL_Quit();
    
    return 0;  
}
