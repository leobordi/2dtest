#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

void set_pixel(SDL_Surface *surface, int x, int y, int r, int g, int b);
void draw_rect(SDL_Surface *surface, int height, int width, bool filled);
void plot_circle_lines(SDL_Surface *surface, int cx, int cy, int x, int y);
void plot_circle_points(SDL_Surface *surface, int cx, int cy, int x, int y);
void draw_circle(SDL_Surface *surface, int cx, int cy, int radius, bool filled);
