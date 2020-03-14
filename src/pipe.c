#include "pipe.h"
#include "object.h"
#include "engine.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define HORIZONTAL_SPACE 150
#define VERTICAL_SPACE 150
//#define STARTED_OFFSET 700
#define PIPE_SPEED 6
#define PIPE_COUNT 6 * 2

static int pipePos = 0;
static Image* image = NULL;

Pipe* Pipe_Init(void) {
    srand(time(NULL));
    image = Image_LoadImage("pipe.png");
    
    int STARTED_OFFSET = staticEngine->width;
    
    Pipe* p = malloc(sizeof(Pipe));
    p->pipes = List_Init();
    
    int i;
    for (i = 0; i < PIPE_COUNT; i += 2) {
        Object* top = Object_Init();
        Object* bottom = Object_Init();
        
        int w = 52;
        int h = staticEngine->height / 2 + staticEngine->height / 4 - 50;
        
        image->width = w;
        image->height = h;
        
        Texture_SetImage(top->texture, image, w, h);
        
        top->texture->angle = 180.0;
        
        int x = top->texture->width * i + i * HORIZONTAL_SPACE + STARTED_OFFSET;
        top->pos->x = x;
        bottom->pos->x = x;
        
        int y = rand() % (top->texture->height - 50);
        // move up texture
        top->pos->y = -y;
        
        bottom->pos->y = top->texture->height - y + VERTICAL_SPACE;
        
        int height = staticEngine->height - bottom->pos->y;
        Texture_SetImage(bottom->texture, image, 52, height);
        
        List_PushBack(p->pipes, top);
        List_PushBack(p->pipes, bottom);
    }
    
    return p;
}

void Pipe_Destroy(void* element) {
    if (element) {
        Pipe* p = (Pipe*)element;
        List_Destroy(p->pipes, Object_Destroy);
        Image_Destroy(image);
        free(element);
    }
}

void Pipe_Update(Pipe *p) {
    if (p) {
        for (ListNode* it = List_Begin(p->pipes); it != NULL; it = List_Next(it)) {
            Object* obj = (Object*)it->data;
            
            obj->pos->x -= PIPE_SPEED;
            
            Object_Update(obj);
        }
    }
}

void Pipe_Render(Pipe* p) {
    if (p) {
        for (ListNode* it = List_Begin(p->pipes); it != NULL; it = List_Next(it)) {
            Object* obj = (Object*)it->data;
            
            Object_Render(obj);
        }
        
        Object* first = (Object*)(List_Begin(p->pipes)->data);
        if (first->pos->x <= pipePos - first->texture->width) {
            pipePos = first->pos->x + first->texture->width;
            
            Object* top = (Object*)List_PopFront(p->pipes);
            Object* bottom = (Object*)List_PopFront(p->pipes);
            
            Object* last = (Object*)(List_End(p->pipes)->data);
            
            int x = last->pos->x + last->texture->width * 2 + HORIZONTAL_SPACE * 2;
            
            top->pos->x = x;
            bottom->pos->x = x;
            
            int y = rand() % (top->texture->height - 50);
            top->pos->y = -y;
            
            bottom->pos->y = top->texture->height - y + VERTICAL_SPACE;
            
            int height = staticEngine->height - bottom->pos->y;
            bottom->texture->height = height;
            
            List_PushBack(p->pipes, top);
            List_PushBack(p->pipes, bottom);
        }
    }
}