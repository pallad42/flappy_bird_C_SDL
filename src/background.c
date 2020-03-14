#include "background.h"
#include "object.h"
#include "engine.h"

#include <stdlib.h>
#include <stdio.h>

#define BG_SPEED 7
#define BG_COUNT 6

static Image* image = NULL;

Background* Background_Init(void) {
    image = Image_LoadImage("bg.jpeg");
    
    Background* bg = malloc(sizeof(Background));
    bg->bgs = List_Init();
        
    int i;
    for (i = 0; i < BG_COUNT; ++i) {
        Object* obj = Object_Init();
        
        Texture_SetImage(obj->texture, image, staticEngine->width / 3, staticEngine->height);
        
        int x = obj->texture->width * i;
        obj->pos->x = x;
        
        List_PushBack(bg->bgs, obj);
    }
    
    return bg;
}

void Background_Destroy(void* element) {
    if (element) {
        Background* bg = (Background*)element;
        List_Destroy(bg->bgs, Object_Destroy);
        Image_Destroy(image);
        free(element);
    }
}

void Background_Render(Background* bg) {
    if (bg) {
        for (ListNode* it = List_Begin(bg->bgs); it != NULL; it = List_Next(it)) {
            Object* obj = (Object*)it->data;
            
            Object_Render(obj);
        }
    }
}

void Background_Update(Background* bg) {
    if (bg) {
        for (ListNode* it = List_Begin(bg->bgs); it != NULL; it = List_Next(it)) {
            Object* obj = (Object*)it->data;
            
            obj->pos->x -= BG_SPEED;
            
            Object_Update(obj);
        }
    
        Object* first = (Object*)(List_Begin(bg->bgs)->data);
        if (first->pos->x <= - first->texture->width) {
            Object* removed = (Object*)List_PopFront(bg->bgs);
            Object* last = (Object*)(List_End(bg->bgs)->data);
            
            removed->pos->x = last->pos->x + last->texture->width;
            
            List_PushBack(bg->bgs, removed);
        }
    }
}