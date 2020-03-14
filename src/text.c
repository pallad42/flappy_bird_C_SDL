#include "text.h"
#include "vector2.h"

#include <stdlib.h>

Text* Text_Init(void) {
    Text* t = malloc(sizeof(Text));
    t->text = String_Init();
    t->font = NULL;
    t->texture = Texture_Init();
    t->color = (SDL_Color){255, 255, 255, 255};
    return t;
}

Text* Text_InitFull(String* text, TTF_Font* font, SDL_Color color, float x, float y) {
    Text* t = Text_Init();
    char* txt = String_CStr(text);
    
    Image* img = Image_LoadText(txt, font, color);
    
    Texture_SetImage(t->texture, img, -1, -1);
    
    Vector2f_SetPos(t->texture->position, x, y);
    
    free(txt);
    
    return t;
}

void Text_Destroy(void* element) {
    if (element) {
        Text* t = (Text*)element;
        Texture_Destroy(t->texture);
        String_Destroy(t->text);
        free(element);
    }
}

void Text_Render(Text* t) {
    if (t) {
        Texture_Render(t->texture);
    }
}