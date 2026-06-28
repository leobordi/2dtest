#pragma once

#include <stdbool.h>
#include "core/window.h"
#include "draw/draw.h"

typedef struct {
	Window window;
	bool running;
} Engine;

Engine engine_init();
void engine_run(Engine *engine);
void engine_handle_event(Engine *engine, SDL_Event *event);
