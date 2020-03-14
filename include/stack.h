#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct StackNode {
	void* value;
	struct StackNode* next;
};

Stack* Stack_Init();
void Stack_Destroy(Stack* s, void (*free_function)(void* element));
void Stack_Push(Stack* s, void* value);
void Stack_Pop(Stack* s, void (*free_function)(void* element));
void* Stack_Peek(Stack* s);
bool Stack_IsEmpty(Stack* s);
int Stack_Size(Stack* s);

#endif