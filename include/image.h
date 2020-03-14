#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "struct_definitions.h"

struct Image {
    int width, height;
    SDL_Texture* rawTexture;
};

Image* Image_Init(void);
void Image_Destroy(void* element);

Image* Image_LoadImage(char* path);
Image* Image_LoadText(char* text, TTF_Font* font, SDL_Color color);

#endif