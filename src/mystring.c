#include "mystring.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

String* String_Init(void) {
	String* s = malloc(sizeof(String));
	s->length = 0;
	s->data = List_Init();
	return s;
}

void String_Append(String* s, ...) {
	if(s) {
		va_list list;
		va_start(list, s);

		char* arg;
		while((arg = va_arg(list, char*)) != NULL) {
			char* newArg = malloc(sizeof(char) * strlen(arg) + 1);
			strcpy(newArg, arg);
			List_PushBack(s->data, newArg);
			size_t argLength = strlen(arg);
			s->length += argLength;
		}

		va_end(list);
	}
}

char* String_CStr(String* s) {
	if (s) {
        size_t size = s->length+1;
        char* result = malloc(sizeof(char) * size);
        result[0] = '\0';
        for (ListNode* it = List_Begin(s->data); it != NULL; it = List_Next(it)) {
            char* ch = (char*)it->data;
            strcat(result, ch);
        }
        return result;
    }
    return NULL;
}

void String_Destroy(void* element) {
	if (element) {
        String* str = (String*)element;
        // free char*
		List_Destroy(str->data, NULL);
		free(element);
	}
}
