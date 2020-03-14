#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

struct ListNode {
    void* data;
    struct ListNode* next;
    struct ListNode* prev;
};

typedef struct List List;
typedef struct ListNode ListNode;

List* List_Init(void);

void List_Destroy(List* list, void (*free_function)(void* element));
void List_Clear(List* list, void (*free_function)(void* element));

void List_PushBack(List* list, void* data);
void List_PushFront(List* list, void* data);
void* List_PopFront(List* list);
void* List_PopBack(List* list);

ListNode* List_Next(ListNode* iterator);
ListNode* List_Prev(ListNode* iterator);
ListNode* List_Begin(List* list);
ListNode* List_End(List* list);

ListNode* List_Remove(List* list, ListNode* iterator, void (*free_function)(void* element));

int List_Contains(List* list, void* element_data, int (*compare_function)(void* a, void* b));
void* List_FindFirst(List* list, void* element_data, int (*compare_function)(void* a, void* b));
void List_BubbleSort(List* list, int (*compare_function)(void* a, void* b));

void List_Reverse(List* list);
void List_Merge(List* from, List* to);
void List_Splice(List* from, List* to, void (*free_function)(void* element));

ListNode* List_Get(List* list, int index);
int List_Size(List* list);
bool List_IsEmpty(List* list);

#endif
