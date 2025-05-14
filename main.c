#include "header.h"

int main(int argc, char *argv[]) {
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    Jeu game;
    game.current_state = MENU_SCREEN;
    game.show_alternate_sprites = 0; // Mode normal par défaut

    // Initialisation fenêtre
    game.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!game.screen) {
        printf("Erreur SDL_SetVideoMode: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialisation ressources
    if (!initialiser_perso(&game)) {
        printf("Erreur initialisation ressources\n");
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Boucle principale
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (game.current_state == MENU_SCREEN) {
                            // Gestion clic menu
                            SDL_Rect pos_single = {
                                (SCREEN_WIDTH - game.button_single->w) / 2,
                                (SCREEN_HEIGHT / 2) - game.button_single->h - 10,
                                game.button_single->w,
                                game.button_single->h
                            };
                            
                            SDL_Rect pos_multi = {
                                (SCREEN_WIDTH - game.button_multi->w) / 2,
                                (SCREEN_HEIGHT / 2) + 10,
                                game.button_multi->w,
                                game.button_multi->h
                            };

                            if (event.button.x >= pos_single.x && 
                                event.button.x <= pos_single.x + pos_single.w &&
                                event.button.y >= pos_single.y && 
                                event.button.y <= pos_single.y + pos_single.h) {
                                game.current_state = SINGLE_PLAYER_SCREEN;
                            }
                            
                            if (event.button.x >= pos_multi.x && 
                                event.button.x <= pos_multi.x + pos_multi.w &&
                                event.button.y >= pos_multi.y && 
                                event.button.y <= pos_multi.y + pos_multi.h) {
                                game.current_state = MULTI_PLAYER_SCREEN;
                            }
                        }
                        else {
                            // Calcul des positions
                            SDL_Rect pos_player = {
                                (SCREEN_WIDTH - game.player_sprites[game.current_player_sprite]->w) / 2,
                                (SCREEN_HEIGHT - game.player_sprites[game.current_player_sprite]->h) / 2,
                                game.player_sprites[game.current_player_sprite]->w,
                                game.player_sprites[game.current_player_sprite]->h
                            };

                            SDL_Rect pos_left = {
                                pos_player.x - game.button_left->w - 20,
                                pos_player.y + (pos_player.h - game.button_left->h) / 2,
                                game.button_left->w,
                                game.button_left->h
                            };

                            // Gestion clic sur cap2.png
                            if (event.button.x >= pos_left.x && 
                                event.button.x <= pos_left.x + pos_left.w &&
                                event.button.y >= pos_left.y && 
                                event.button.y <= pos_left.y + pos_left.h) {
                                
                                game.show_alternate_sprites = !game.show_alternate_sprites;
                            }
                            // Gestion clic sur le personnage (si en mode normal)
                            else if (!game.show_alternate_sprites &&
                                     event.button.x >= pos_player.x && 
                                     event.button.x <= pos_player.x + pos_player.w &&
                                     event.button.y >= pos_player.y && 
                                     event.button.y <= pos_player.y + pos_player.h) {
                                // Changer entre v1, v2, v3
                                game.current_player_sprite = (game.current_player_sprite + 1) % 3;
                            }
                        }
                    }
                    break;
            }
        }

      
        SDL_FillRect(game.screen, NULL, SDL_MapRGB(game.screen->format, 0, 0, 0));
        
        switch (game.current_state) {
            case MENU_SCREEN:
                afficher_menu(&game);
                break;
            case SINGLE_PLAYER_SCREEN:
            case MULTI_PLAYER_SCREEN:
                afficher_joueur(&game);
                break;
        }

        SDL_Flip(game.screen);
        SDL_Delay(16);
    }

   
    for (int i = 0; i < 3; i++) {
        if (game.player_sprites[i]) SDL_FreeSurface(game.player_sprites[i]);
    }
    SDL_FreeSurface(game.j2_sprite);

    SDL_FreeSurface(game.background);
    SDL_FreeSurface(game.button_single);
    SDL_FreeSurface(game.button_multi);
    SDL_FreeSurface(game.button_left);
    SDL_FreeSurface(game.button_right);
    if (game.font) TTF_CloseFont(game.font);
SDL_FreeSurface(game.button_custom);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
