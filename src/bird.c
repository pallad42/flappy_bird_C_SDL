#include "bird.h"
#include "engine.h"
#include "SDL2/SDL_mixer.h"
#include "linked_list.h"
#include "pipe.h"
#include "level.h"

#include <stdlib.h>
#include <stdio.h>

static Image* image = NULL;
static float delta = 5.0f;
static ListNode* nextPipe = NULL;

static Mix_Chunk* pointWAV = NULL;
static Mix_Chunk* wingWAV = NULL;
static Mix_Chunk* hitWAV = NULL;

static bool Bird_Collision(Object* a, Object* b) {
    if (a && b) {
        float aX = a->pos->x;
        float aY = a->pos->y;
        int aW = a->texture->width;
        int aH = a->texture->height;
        
        float bX = b->pos->x;
        float bY = b->pos->y;
        int bW = b->texture->width;
        int bH = b->texture->height;
        
        if (aX + aW >= bX &&
            aX <= bX + bW &&
            aY + aH >= bY &&
            aY <= bY + bH) {
                return true;
            }
    }
    return false;
}

Bird* Bird_Init(Pipe* p, Level* lvl) {
    image = Image_LoadImage("bird.png");
    
    Bird* b = malloc(sizeof(Bird));
    b->base.texture = Texture_Init();
    b->base.pos = Vector2f_Init();
    b->score = 0;
    
    b->pipe = p;
    b->lvl = lvl;
    
    Texture_SetImage(b->base.texture, image, 50, 50);
        
    int x = staticEngine->width / 2 - b->base.texture->width / 2;
    int y = staticEngine->height / 2 - b->base.texture->height / 2;
    
    Vector2f_SetPos(b->base.pos, x, y);
    
    nextPipe = List_Begin(p->pipes);
    
    pointWAV = Mix_LoadWAV("sfx_point.wav");
    wingWAV = Mix_LoadWAV("sfx_wing.wav");
    hitWAV = Mix_LoadWAV("sfx_hit.wav");
    
    return b;
}

void Bird_Destroy(void* element) {
    if (element) {
        Bird* b = (Bird*)element;
        Texture_Destroy(b->base.texture);
        Vector2f_Destroy(b->base.pos);
        Image_Destroy(image);
        
        Mix_FreeChunk(pointWAV);
        Mix_FreeChunk(wingWAV);
        Mix_FreeChunk(hitWAV);
        
        free(element);
    }
}

void Bird_Update(Bird* b) {
    if (b) {
        delta += 0.5f;
        delta = delta >= 10.0f ? 10.0f : delta;
        b->base.pos->y += delta;
        b->base.texture->angle = delta * 3.0f;
        
        Object_Update(&b->base);
        
        // collision
        if (!b->lvl->pause) {
            Object* top = (Object*)nextPipe->data;
            Object* bottom = (Object*)nextPipe->next->data;
            if (Bird_Collision(&b->base, top) || Bird_Collision(&b->base, bottom) || 
                b->base.pos->y < 0 || b->base.pos->y >= staticEngine->height) {
                Mix_PlayChannel(-1, hitWAV, 0);
                b->lvl->pause = true;
            } else {
                // score
                Object* obj = (Object*)nextPipe->data;
                if (obj) {
                    float dst = obj->pos->x - b->base.pos->x;
                    if (dst <= 0) {
                        b->score++;

                        nextPipe = List_Next(nextPipe);
                        // skip bottom
                        nextPipe = List_Next(nextPipe);
                        
                        Mix_PlayChannel(-1, pointWAV, 0);
                    }
                }
            }
        }
    }
}

void Bird_Render(Bird* b) {
    if (b) {
        Object_Render(&b->base);
    }
}

void Bird_HandleEvent(Bird* b, SDL_Event* e) {
    if (b && e) {
        if (e->key.keysym.sym == SDLK_SPACE && e->type == SDL_KEYDOWN) {
            delta = -10.0f;
            Mix_PlayChannel(-1, wingWAV, 0);
        }
    }
}