#include "linked_list.h"
#include <stdlib.h>

struct List {
    ListNode* begin;
    ListNode* end;
    int size;
};

static ListNode* ListNode_Init(void* data) {
	ListNode* n = malloc(sizeof(ListNode));
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

static void* List_Erase(List* list, ListNode* from) {
    if (list && from) {
		if(list->size) {
			if(list->size > 1) {
				// prev is head/begin
				if(!from->prev && from->next) {
					list->begin->next = from->next;
					from->next->prev = NULL;
				}
				else if(from->prev && from->next) {
					from->prev->next = from->next;
					from->next->prev = from->prev;
				}
				// next is tail/end
				else if(from->prev && !from->next) {
					list->end->prev = from->prev;
					from->prev->next = NULL;
				}
			} else {
				list->begin->next = NULL;
				list->end->prev = NULL;
			}

			list->size--;
            
            void* result = from->data;
			
            free(from);
            //ListNode_Destroy(from);
            
            return result;
		}
	}
    return NULL;
}

static void List_Swap(ListNode* n1, ListNode* n2) {
    if (n1 && n2) {
		void* data = n1->data;
		n1->data = n2->data;
		n2->data = data;
	}
}

List* List_Init(void) {
    List* list = malloc(sizeof(List));
    list->begin = ListNode_Init(NULL);
    list->end = ListNode_Init(NULL);
    list->size = 0;
    return list;
}

void List_PushBack(List* list, void* data) {
    if (list) {
		ListNode* n = ListNode_Init(data);
		if(list->size == 0) {
			ListNode* first = list->begin;
			first->next = n;
		} else {
			ListNode* last = list->end->prev;
			last->next = n;
			n->prev = last;
		}
		list->end->prev = n;
		list->size++;
	}
}

void List_PushFront(List* list, void* data) {
    if (list) {
		ListNode* n = ListNode_Init(data);
		if(list->size == 0) {
			ListNode* last = list->end;
			last->prev = n;
		} else {
			ListNode* first = list->begin->next;
			first->prev = n;
			n->next = first;
		}
		list->begin->next = n;
		list->size++;
	}
}

ListNode* List_Next(ListNode* iterator) {
    return iterator ? iterator->next : NULL;
}

ListNode* List_Prev(ListNode* iterator) {
    return iterator ? iterator->prev : NULL;
}

ListNode* List_Begin(List* list) {
    return list ? list->begin->next : NULL;
}

ListNode* List_End(List* list) {
    return list ? list->end->prev : NULL;
}

void List_Clear(List* list, void (*free_function)(void* element)) {
    if (list) {
		while(list->size) {
			void* data = List_PopBack(list);
            if (free_function) {
                free_function(data);
            }
		}
	}
}

void* List_PopFront(List* list) {
    return List_Erase(list, List_Begin(list));
}

void* List_PopBack(List* list) {
    return List_Erase(list, List_End(list));
}

void List_Destroy(List* list, void (*free_function)(void* element)) {
    if(list) {
		List_Clear(list, free_function);
		free(list->begin);
		free(list->end);
		free(list);
	}
}

int List_Contains(List* list, void* element_data, int (*compare_function)(void* a, void* b)) {
    if (list && compare_function) {
		for(ListNode* it = List_Begin(list); it != NULL; it = List_Next(it)) {
			if(compare_function(element_data, it->data) == 0) {
				return 1;
			}
		}
	}
    return 0;
}

void* List_FindFirst(List* list, void* element_data, int (*compare_function)(void* a, void* b)) {
    if (list && compare_function) {
		for(ListNode* it = List_Begin(list); it != NULL; it = List_Next(it)) {
			if(compare_function(element_data, it->data) == 0) {
				return it->data;
			}
		}
	}
    return NULL;
}

ListNode* List_Get(List* list, int index) {
    if(list && index >= 0 && index < list->size) {
        int counter = 0;
        for(ListNode* it = List_Begin(list); it != NULL; it = List_Next(it)) {
            if(counter++ == index) {
                return it;
            }
        }
    }
    return NULL;
}

void List_BubbleSort(List* list, int (*compare_function)(void* a, void* b)) {
    if (list && compare_function) {
		for(ListNode* it1 = List_Begin(list); it1 != NULL; it1 = List_Next(it1)) {
			for(ListNode* it2 = it1->next; it2 != NULL; it2 = List_Next(it2)) {
				if(compare_function(it1->data, it2->data) > 0) {
					List_Swap(it1, it2);
				}
			}
		}
	}
}

ListNode* List_Remove(List* list, ListNode* iterator, void (*free_function)(void* element)) {
    if (list && iterator && free_function) {
		ListNode* next = iterator->next;
		void* data = List_Erase(list, iterator);
        free_function(data);
		return next;
	}
	return NULL;
}

void List_Reverse(List* list) {
    if (list) {
		ListNode* begin = List_Begin(list);
		ListNode* end = List_End(list);
		int size = list->size / 2;
		while(size--) {
			List_Swap(begin, end);
			begin = begin->next;
			end = end->prev;
		}
	}
}

void List_Merge(List* from, List* to) {
    if (from && to) {
		if(from != to) {
			for(ListNode* it = List_Begin(from); it != NULL; it = List_Next(it)) {
				List_PushBack(to, it->data);
			}
		}
	}
}

void List_Splice(List* from, List* to, void (*free_function)(void* element)) {
    List_Merge(from, to);
    List_Destroy(from, free_function);
}

int List_Size(List* list) {
    return list ? list->size : 0;
}

bool List_IsEmpty(List* list) {
    return List_Size(list) > 0 ? true : false;
}

