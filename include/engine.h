#ifndef ENGINE_H
#define ENGINE_H

#include "SDL2/SDL.h"
#include "logger.h"
#include "struct_definitions.h"

#include <stdbool.h>

struct Engine {
    int width, height;
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Logger* logger;
};

// STATIC CONST POINTER
extern Engine* staticEngine;

Engine* Engine_Init(char* title, int width, int height);
void Engine_Destroy(void* element);

void Engine_Start(Engine* engine);

#endif
