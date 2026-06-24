#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define NUMPOINTS 10000

void clear(SDL_Surface *surface) {
    memset((uint8_t *)surface->pixels, 0, surface->h * surface->pitch);
}

void draw(SDL_Surface *surface) {
    int width = surface->w;
    int height = surface->h; 

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            uint8_t *fb = (uint8_t*)surface->pixels;
            fb[x + y] = 1;
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("Errore di inizializzazione: %s\n", SDL_GetError());
        exit(-1);
    }
    
    SDL_Window *window = SDL_CreateWindow("2D test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 900, SDL_WINDOW_SHOWN); 
    if (!window) {
        printf("Errore di creazione finestra!\n");
        exit(-1);
    } 
 
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    clear(surface);

    draw(surface);

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
