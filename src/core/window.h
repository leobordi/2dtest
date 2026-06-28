#pragma once

#include <SDL2/SDL.h>

typedef struct {
	SDL_Window *window;
	SDL_Surface *surface;
} Window;

Window window_init();
void window_close(SDL_Window *window);
void window_clear(SDL_Surface *surface);
void surface_clear(SDL_Surface *surface);
