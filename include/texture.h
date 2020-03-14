#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "vector2.h"
#include "image.h"
#include "struct_definitions.h"

struct Texture {
    int width, height;
    Vector2f* position;
    Image* img;
    double angle;
    SDL_Point center;
    SDL_RendererFlip flip;
};

Texture* Texture_Init(void);
void Texture_Destroy(void* element);

void Texture_Render(Texture* t);

void Texture_SetImage(Texture* t, Image* img, int width, int height);
void Texture_SetPosition(Texture* t, float x, float y);

#endif