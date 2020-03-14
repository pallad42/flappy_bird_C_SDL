#ifndef PIPE_H
#define PIPE_H

#include "struct_definitions.h"

#include "linked_list.h"

struct Pipe {
    List* pipes; // struct Object
};

Pipe* Pipe_Init(void);
void Pipe_Destroy(void* element);

void Pipe_Update(Pipe *p);
void Pipe_Render(Pipe* p);

#endif