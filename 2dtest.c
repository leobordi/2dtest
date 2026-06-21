#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("Errore di inizializzazione: %s\n", SDL_GetError());
        exit(-1);
    }
    
    SDL_Window *window = SDL_CreateWindow(
        "2D test",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        1500,
        900,
        SDL_WINDOW_SHOWN 
    ); 

    if (window == NULL) {
        printf("Errore di creazione finestra!\n");
        exit(-1);
    } 
 
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (1) {    
        SDL_Event event;
        bool exit = false;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit = true;
                    break;
            }
        }

        if (exit) break;
    }
    
    return 0;
}
