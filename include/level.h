#ifndef LEVEL_H
#define LEVEL_H

#include "struct_definitions.h"
#include "SDL2/SDL.h"

#include <stdbool.h>

struct Level {
    Background* bg;
    Pipe* pipe;
    Bird* bird;
    bool pause;
};

Level* Level_Init(void);
void Level_Destroy(void* element);

void Level_Update(Level* lvl);
void Level_Render(Level* lvl);
void Level_HandleEvent(Level* lvl, SDL_Event* e);

#endif