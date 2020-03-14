#include "object.h"

#include <stdlib.h>

Object* Object_Init(void) {
    Object* obj = malloc(sizeof(Object));
    obj->texture = Texture_Init();
    obj->pos = Vector2f_Init();
    return obj;
}

void Object_Destroy(void* element) {
    if (element) {
        Object* obj = (Object*)element;
        Vector2f_Destroy(obj->pos);
        Texture_Destroy(obj->texture);
        free(element);
    }
}

void Object_Update(Object* obj) {
    if (obj) {
        Texture_SetPosition(obj->texture, obj->pos->x, obj->pos->y);
    }
}

void Object_Render(Object* obj) {
    if (obj) {
        Texture_Render(obj->texture);
    }
}
