#ifndef TEXT_H
#define TEXT_H

#include "struct_definitions.h"
#include "texture.h"
#include "mystring.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"

struct Text {
    String* text;
    Texture* texture;
    TTF_Font* font;
    SDL_Color color;
};

Text* Text_Init(void);
Text* Text_InitFull(String* text, TTF_Font* font, SDL_Color color, float x, float y);

void Text_Destroy(void* element);

void Text_Render(Text* t);

#endif