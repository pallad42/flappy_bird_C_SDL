#include "level.h"
#include "SDL2/SDL_ttf.h"
#include "engine.h"
#include "texture.h"
#include "bird.h"
#include "pipe.h"
#include "background.h"
#include "text.h"

#include <stdlib.h>
#include <stdio.h>

static TTF_Font* consolasFont = NULL;

static Text* t1 = NULL;
static Text* t2 = NULL;

Level* Level_Init(void) {
    Level* lvl = malloc(sizeof(Level));
    lvl->bg = Background_Init();
    lvl->pipe = Pipe_Init();
    lvl->bird = Bird_Init(lvl->pipe, lvl);
    lvl->pause = false;
    
    consolasFont = TTF_OpenFont("consola.ttf", 30);
    
    String* txt = String_Init();
    String_Append(txt, "Game Over", NULL);
    t1 = Text_InitFull(txt, consolasFont, (SDL_Color){0, 0, 0, 255}, 0.0f, 0.0f);
    Vector2f_SetPos(t1->texture->position, 
                    (staticEngine->width - t1->texture->img->width) / 2.0f, 
                    (staticEngine->height - t1->texture->img->height) / 2.0f);
    
    String* txt2 = String_Init();
    String_Append(txt2, "Press ENTER to try again or ESCAPE to exit!", NULL);
    t2 = Text_InitFull(txt2, consolasFont, (SDL_Color){0, 0, 0, 255}, 0.0f, 0.0f);
    Vector2f_SetPos(t2->texture->position, 
                    (staticEngine->width - t2->texture->img->width) / 2.0f, 
                    (staticEngine->height - t2->texture->img->height) / 2.0f + 80.0f);
    
    return lvl;
}

void Level_Destroy(void* element) {
    if (element) {
        Level* lvl = (Level*)element;
        
        Background_Destroy(lvl->bg);
        Pipe_Destroy(lvl->pipe);
        Bird_Destroy(lvl->bird);
        
        TTF_CloseFont(consolasFont);
        
        free(element);
    }
}

void Level_Update(Level* lvl) {
    if (lvl) {
        if (!lvl->pause) {
            Background_Update(lvl->bg);
            Pipe_Update(lvl->pipe);
        }
        Bird_Update(lvl->bird);
    }
}

void Level_Render(Level* lvl) {
    if (lvl) {
        Background_Render(lvl->bg);
        Pipe_Render(lvl->pipe);
        Bird_Render(lvl->bird);
        
        if (lvl->pause) {
            Text_Render(t1);
            
            char score[16];
            sprintf(score, "%d", lvl->bird->score);
            
            String* txt = String_Init();
            String_Append(txt, "Score: ", score, NULL);
            Text* t = Text_InitFull(txt, consolasFont, (SDL_Color){0, 255, 0, 255}, 0.0f, 0.0f);
            Vector2f_SetPos(t->texture->position, 
                            (staticEngine->width - t->texture->img->width) / 2.0f,
                            (staticEngine->height - t->texture->img->height) / 2.0f + 40.0f);
            Text_Render(t); 
            Text_Destroy(t);
            
            Text_Render(t2);
        } else {
            char score[16];
            sprintf(score, "%d", lvl->bird->score);
            
            String* txt = String_Init();
            String_Append(txt, "Score: ", score, NULL);
            Text* t = Text_InitFull(txt, consolasFont, (SDL_Color){255, 0, 0, 255}, 0.0f, 0.0f);
            Vector2f_SetPos(t->texture->position, 
                            (staticEngine->width - t->texture->img->width) / 2.0f, 
                            0.0f);
            Text_Render(t); 
            Text_Destroy(t);
        }
    }
}

void Level_HandleEvent(Level* lvl, SDL_Event* e) {
    if (lvl && e) {
        Bird_HandleEvent(lvl->bird, e);
    }
}