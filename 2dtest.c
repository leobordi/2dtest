#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

void clear(SDL_Surface *surface) {
    memset((uint8_t *)surface->pixels, 0, surface->h * surface->pitch);
}

void set_pixel(SDL_Surface *surface, int x, int y, int r, int g, int b) {
    int width = surface->w;
    int height = surface->h;
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;

    int pitch = surface->pitch;

    uint8_t *fb = (uint8_t *)surface->pixels;

    /* RGBA8888
    * pitch = bytes per row
    * y * pitch = row start
    * x * 4 = pixel start
    * + 0..1..2..3 = r g b a
    */
    fb[y * pitch + x * 4 + 0] = r;
    fb[y * pitch + x * 4 + 1] = g;
    fb[y * pitch + x * 4 + 2] = b;
    fb[y * pitch + x * 4 + 3] = 255;
}

void draw_rect(SDL_Surface *surface, int height, int width, bool filled) {
    int x_start = ((surface->w / 2) - (width / 2));
    int y_start = ((surface->h / 2) - (height / 2));

    if (filled) {
        for (int x = x_start; x < x_start + width; x++) {
            for (int y = y_start; y < y_start + height; y++) {
                set_pixel(surface, x, y, 150, 150, 255);
            }
        }
    } 
    else {
        for (int x = x_start; x < x_start + width; x++) {
            set_pixel(surface, x, y_start, 150, 150, 255);
            set_pixel(surface, x, y_start + height, 150, 150, 255);
        }
        for (int y = y_start; y < y_start + height; y++) {
            set_pixel(surface, x_start, y, 150, 150, 255);
            set_pixel(surface, x_start + width, y, 150, 150, 255);
        }        
    }
}

void plot_circle_lines(SDL_Surface *surface, int cx, int cy, int x, int y) {
    for (int i = cx - x; i <= cx + x; i++) {
        set_pixel(surface, i, cy + y, 255, 255, 255);
        set_pixel(surface, i, cy - y, 255, 255, 255);
    }
    for (int i = cx - y; i <= cx + y; i++) {
        set_pixel(surface, i, cy + x, 255, 255, 255);
        set_pixel(surface, i, cy - x, 255, 255, 255);
    }
}

void plot_circle_points(SDL_Surface *surface, int cx, int cy, int x, int y) {
    set_pixel(surface, cx - x, cy + y, 255, 255, 255);
    set_pixel(surface, cx - x, cy - y, 255, 255, 255);
    set_pixel(surface, cx - y, cy + x, 255, 255, 255);
    set_pixel(surface, cx + y, cy - x, 255, 255, 255);

    set_pixel(surface, cx + x, cy + y, 255, 255, 255);
    set_pixel(surface, cx + x, cy - y, 255, 255, 255);
    set_pixel(surface, cx + y, cy + x, 255, 255, 255);
    set_pixel(surface, cx + y, cy - x, 255, 255, 255);
}

void draw_circle(SDL_Surface *surface, int cx, int cy, int radius, bool filled) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;

    if (filled) {
        plot_circle_lines(surface, cx, cy, x, y);
    } else {
        plot_circle_points(surface, cx, cy, x, y);
    }

    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }

        x++;

        if (filled) {
            plot_circle_lines(surface, cx, cy, x, y);
        } else {
            plot_circle_points(surface, cx, cy, x, y);
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
    draw_rect(surface, 400, 400, true);
    draw_circle(surface, 750, 450, 200, true);#000000#FFFFFF#FFFFFF#FFFFFF#F9FFFF#FFFFFF
    SDL_UpdateWindowSurface(window);

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

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit(); 
    return 0;
}
