#include "texture.h"
#include "engine.h"
#include "SDL2/SDL_image.h"

#include <stdlib.h>

Texture* Texture_Init(void) {
    Texture* t = malloc(sizeof(Texture));
    t->position = Vector2f_Init();
    t->img = NULL;
    t->angle = 0.0;
    t->width = 0;
    t->height = 0;
    t->center.x = 0;
    t->center.y = 0;
    t->flip = SDL_FLIP_NONE;
    return t;
}

void Texture_Destroy(void* element) {
    if (element) {
        free(element);
    }
}

void Texture_SetImage(Texture* t, Image* img, int width, int height) {
    if (t && img) {
        t->img = img;
        t->width = width <= -1 ? t->img->width : width;
        t->height = height <= -1 ? t->img->height : height;
        t->center.x = t->width / 2;
        t->center.y = t->height / 2;
    }
}

void Texture_Render(Texture* t) {
    if (t) {
        SDL_Rect src = (SDL_Rect){.x=0, .y=0, .w=t->img->width, .h=t->img->height};
        SDL_Rect dst = (SDL_Rect){.x=t->position->x, .y=t->position->y, .w=t->width, .h=t->height};
        SDL_RenderCopyEx(staticEngine->renderer, t->img->rawTexture, &src, &dst, t->angle, &t->center, t->flip);
    }
}

void Texture_SetPosition(Texture* t, float x, float y) {
    if (t) {
        Vector2f_SetPos(t->position, x, y);
    }
}
