#include "engine.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "level.h"

#include <stdlib.h>

Engine* staticEngine = NULL;

static Level* lvl = NULL;

static void Engine_Update(Engine* engine) {
    Logger_PrintInfo(engine->logger);
    Logger_PrintError(engine->logger);
    
    if (lvl) {
        if (lvl->pause) {
            SDL_Event e;
            SDL_PollEvent(&e);
            if(e.key.keysym.sym == SDLK_RETURN) {
                Level_Destroy(lvl);
                lvl = Level_Init();
            }
        }
        Level_Update(lvl);
    }
}

static void Engine_Render(Engine* engine) {
    SDL_RenderClear(engine->renderer);
    
    // render here
    Level_Render(lvl);
    //
    
    SDL_RenderPresent(engine->renderer);
}

static void Engine_HandleEvent(Engine* engine) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            engine->running = false;
        }
        
        if(e.key.keysym.sym == SDLK_ESCAPE) {
            engine->running = false;
        }
        
        if (lvl && !lvl->pause) {
            Level_HandleEvent(lvl, &e);
        }
    }
}

static bool Engine_InitSDL(Logger* logger) {
    if (logger) {
        // SDL init
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            Logger_AppendError(logger, "Unable to initialize SDL: ", SDL_GetError(), NULL);
            return false;
        }
        
        // IMG init
        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        if ((IMG_Init(flags) & flags) != flags) {
            Logger_AppendError(logger, "Unable to initialize IMG: ", IMG_GetError(), NULL);
            return false;
        }
        
        // TTF init
        if (TTF_Init() == -1) {
            Logger_AppendError(logger, "Unable to initialize TTF: ", TTF_GetError(), NULL);
            return false; 
        }
        
        // MIX init
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
            Logger_AppendError(logger, "Unable to initialize MIX: ", Mix_GetError(), NULL);
            return false; 
        }
        
        return true;
    }
    return false;
}

static void Engine_DestroySDL() {
    SDL_Quit();
    IMG_Quit();
    TTF_Init();
    Mix_Quit();
}

Engine* Engine_Init(char* title, int width, int height) {
    Logger* logger = Logger_Init();
    
    bool running = Engine_InitSDL(logger);
    
    SDL_Window* window = SDL_CreateWindow(title, 
                                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                            width, height, 
                                            SDL_WINDOW_SHOWN);
    
    if (!window) {
        Logger_AppendError(logger, "Could not create window: ", SDL_GetError(), NULL);
        running = false;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        Logger_AppendError(logger, "Could not create renderer: ", SDL_GetError(), NULL);
        running = false;
    }

    Engine* e = malloc(sizeof(Engine));
    e->width = width;
    e->height = height;
    e->running = running;
    e->window = window;
    e->renderer = renderer;
    e->logger = logger;
    
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    
    return e;
}

void Engine_Destroy(void* element) {
    if (element) {
        Engine* engine = (Engine*)element;
        SDL_DestroyRenderer(engine->renderer);
        SDL_DestroyWindow(engine->window);
        Logger_Destroy(engine->logger);
        Level_Destroy(lvl);
        free(element);
    }
    Engine_DestroySDL();
}

void Engine_Start(Engine* engine) {
    if (engine) {
        Logger_AppendInfo(engine->logger, "Successfully initialization", NULL);
        
        lvl = Level_Init();
        
        while (engine->running) {
            Engine_HandleEvent(engine);
            Engine_Update(engine);
            Engine_Render(engine);
        }
    }
}