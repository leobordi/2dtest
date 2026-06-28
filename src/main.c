#include "core/engine.h"

int main() {
	Engine e = engine_init();
	engine_run(&e);
	
	return 0;
}
