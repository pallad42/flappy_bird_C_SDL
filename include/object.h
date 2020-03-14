#ifndef OBJECT_H
#define OBJECT_H

#include "texture.h"
#include "struct_definitions.h"

struct Object {
    Vector2f* pos;
    Texture* texture;
};

Object* Object_Init(void);
void Object_Destroy(void* element);

void Object_Update(Object* obj);
void Object_Render(Object* obj);

#endif