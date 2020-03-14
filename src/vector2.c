#include "vector2.h"

#include <stdlib.h>

Vector2i* Vector2i_Init(void) {
    Vector2i* vec = malloc(sizeof(Vector2i));
    vec->x = 0;
    vec->y = 0;
    return vec;
}

Vector2f* Vector2f_Init(void) {
    Vector2f* vec = malloc(sizeof(Vector2f));
    vec->x = 0;
    vec->y = 0;
    return vec;
}

void Vector2i_Destroy(void* element) {
    if (element) {
        free(element);
    }
}

void Vector2f_Destroy(void* element) {
    if (element) {
        free(element);
    }
}

void Vector2i_SetPos(Vector2i* vec, int x, int y) {
    if (vec) {
        vec->x = x;
        vec->y = y;
    }
}

void Vector2f_SetPos(Vector2f* vec, float x, float y) {
    if (vec) {
        vec->x = x;
        vec->y = y;
    }
}