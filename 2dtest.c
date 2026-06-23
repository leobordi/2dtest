#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define HEIGHT 900 
#define WIDTH 1500

void buffer_clear(int *buffer) {
    for (int i = 0; i < HEIGHT*WIDTH; i++) {
        buffer[i] = 0;
    }
}

void draw(int *buffer, int *points, int num) {
    for (int i = 0; i < num; i++) {
        for (int k = points[i]; k < points[i+1]-points[i]; k++) {
            buffer[k] = 1;
        }
    }
}

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
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    
    int buffer[HEIGHT*WIDTH];
    int point_ori = HEIGHT/2 * WIDTH/2;
    
    buffer_clear(buffer);
    int points[2] = {0, 200};

    draw(buffer, points, 2);
    SDL_UpdateTexture(texture, NULL, buffer, 64 * sizeof(int));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
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
