#include "image.h"
#include "SDL2/SDL_image.h"
#include "engine.h"

#include <stdlib.h>

Image* Image_Init(void) {
    Image* img = malloc(sizeof(Image));
    img->width = 0;
    img->height = 0;
    img->rawTexture = NULL;
    return img;
}

void Image_Destroy(void* element) {
    if (element) {
        Image* img = (Image*)element;
        SDL_DestroyTexture(img->rawTexture);
        free(element);
    }
}

Image* Image_LoadImage(char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        Logger_AppendError(staticEngine->logger, "Unable to load image '", path, "'. [SDL Message]: ", IMG_GetError(), NULL);
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(staticEngine->renderer, surface);
    if (!texture) {
        Logger_AppendError(staticEngine->logger, "Unable to create texture from image'", path, "'. [SDL Message]: ", SDL_GetError(), NULL);
        SDL_FreeSurface(surface);
        return NULL;
    }
    
    Image* img = Image_Init();
    img->rawTexture = texture;
    img->width = surface->w;
    img->height = surface->h;
    
    SDL_FreeSurface(surface);
    
    return img;
}

Image* Image_LoadText(char* text, TTF_Font* font, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (!surface) {
        Logger_AppendError(staticEngine->logger, "Unable to render text. [SDL Message]: ", TTF_GetError(), NULL);
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(staticEngine->renderer, surface);
    if (!texture) {
        Logger_AppendError(staticEngine->logger, "Unable to create texture from text. [SDL Message]: ", SDL_GetError(), NULL);
        SDL_FreeSurface(surface);
        return NULL;
    }
    
    Image* img = Image_Init();
    img->rawTexture = texture;
    img->width = surface->w;
    img->height = surface->h;
    
    SDL_FreeSurface(surface);
    
    return img;
}
