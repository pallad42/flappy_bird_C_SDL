#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct Stack {
	int size;
	StackNode* head;
};

static StackNode* Stack_Create(void* value) {
	StackNode* s = malloc(sizeof(StackNode));
	s->value = value;
	s->next = NULL;
	return s;
}

Stack* Stack_Init() {
	Stack* s = malloc(sizeof(Stack));
	s->size = 0;
	s->head = NULL;
	return s;
}

void Stack_Destroy(Stack* s, void (*free_function)(void* element)) {
	if (s) {
        while (!Stack_IsEmpty(s)) {
            Stack_Pop(s, free_function);
        }
    }
}

void Stack_Push(Stack* s, void* value) {
	if (s) {
		StackNode* node = Stack_Create(value);
		node->next = s->head;
		s->head = node;
		s->size++;
	}
}

void Stack_Pop(Stack* s, void (*free_function)(void* element)) {
	if (!Stack_IsEmpty(s)) {
		StackNode* node = s->head->next;
		void* value = s->head->value;
        if (free_function && value) {
            free_function(value);
        }
		free(s->head);
		s->head = node;
		s->size--;
	}
}

void* Stack_Peek(Stack* s) {
	return s && s->head ? s->head->value : NULL;
}

bool Stack_IsEmpty(Stack* s) {
	return s && s->size > 0 ? false : true;
}

int Stack_Size(Stack* s) {
    return s ? s->size : 0;
}