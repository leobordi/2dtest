#include "core/engine.h"

Engine engine_init() {
	Engine engine;
	engine.window = window_init(1500, 900);
	surface_clear(engine.window.surface);
	return engine;
}

void engine_run(Engine *engine) {
	SDL_Event event;
    
    //draw_circle(engine->window.surface, 750, 450, 200, false);    
	//SDL_UpdateWindowSurface(engine->window.window);
	
	while (engine->running) {    

        while (SDL_PollEvent(&event)) {
            engine_handle_event(engine, &event);
        }

        SDL_Delay(16);
    }
    
    window_close(engine->window.window);
}

void engine_handle_event(Engine *engine, SDL_Event *event) {
	switch (event->type) {
		case SDL_QUIT:
			engine->running = false;
			break;
	}
}
