#include "core/window.h"

Window window_init() {
	Window window;
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("Errore di inizializzazione: %s\n", SDL_GetError());
        exit(-1);
    }
    
    window.window = SDL_CreateWindow("2D test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 900, SDL_WINDOW_SHOWN); 
    if (!window.window) {
        printf("Errore di creazione finestra!\n");
        exit(-1);
    } 
 
	window.surface = SDL_GetWindowSurface(window.window);
    if (!window.surface) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        SDL_DestroyWindow(window.window);
        SDL_Quit();
        exit(-1);
    }
    
    return window;
}

void surface_clear(SDL_Surface *surface) {
    memset((uint8_t *)surface->pixels, 0, surface->h * surface->pitch);
}

void window_close(SDL_Window *window) {
	SDL_DestroyWindow(window);
    SDL_Quit();
}
