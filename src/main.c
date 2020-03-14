#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

int main(int argc, char** argv) {
	Engine* engine = Engine_Init("flappy_bird_c_sdl", 800, 600);
//	Engine* engine = Engine_Init("sdl_game", 1600, 900);
    staticEngine = engine;
    
    Engine_Start(engine);
    
    Engine_Destroy(engine);
    engine = NULL;
    
	//printf("\n\nPress enter to exit..."); getchar();
	return 0;
}
