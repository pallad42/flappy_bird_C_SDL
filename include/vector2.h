#ifndef VECTOR_H
#define VECTOR_H

#include "struct_definitions.h"

struct Vector2i {
    int x, y;
};

struct Vector2f {
    float x, y;
};

Vector2i* Vector2i_Init(void);
Vector2f* Vector2f_Init(void);

void Vector2i_Destroy(void* element);
void Vector2f_Destroy(void* element);

void Vector2i_SetPos(Vector2i* vec, int x, int y);
void Vector2f_SetPos(Vector2f* vec, float x, float y);

#endif