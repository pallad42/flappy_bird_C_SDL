#ifndef BIRD_H
#define BIRD_H

#include "object.h"
//#include "pipe.h"
//#include "level.h"

#include "struct_definitions.h"

//typedef struct Level Level;

struct Bird {
    Object base;
    Pipe* pipe;
    Level* lvl;
    int score;
};

Bird* Bird_Init(Pipe* p, Level* lvl);
void Bird_Destroy(void* element);

void Bird_Update(Bird* b);
void Bird_Render(Bird* b);
void Bird_HandleEvent(Bird* b, SDL_Event* e);

#endif