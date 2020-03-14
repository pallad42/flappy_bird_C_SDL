#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "linked_list.h"
#include "struct_definitions.h"

struct Background {
    List* bgs; // struct Object
};

Background* Background_Init(void);
void Background_Destroy(void* element);

void Background_Render(Background* bg);
void Background_Update(Background* bg);

#endif