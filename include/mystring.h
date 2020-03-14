#ifndef STRING_H
#define STRING_H

#include "linked_list.h"

struct String {
	int length;
	List* data;
};

typedef struct String String;

String* String_Init(void);
void String_Append(String* s, ...);
char* String_CStr(String* s);
void String_Destroy(void* element);

#endif