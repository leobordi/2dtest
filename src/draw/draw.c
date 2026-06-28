#include "draw/draw.h"

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
