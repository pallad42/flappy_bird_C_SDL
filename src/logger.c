#include "logger.h"
#include "mystring.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

static void Logger_Print(Logger* logger, char* title, Stack* src) {
    if (logger && src) {
        while (!Stack_IsEmpty(src)) {
            String* str = (String*)Stack_Peek(src);
            Stack_Pop(src, NULL);
            char* msg = String_CStr(str);
            printf("%s: %s\n", title, msg);
            free(msg);
        }
    }
}

Logger* Logger_Init(void) {
    Logger* logger = malloc(sizeof(Logger));
    logger->info = Stack_Init();
    logger->error = Stack_Init();
    return logger;
}

void Logger_Destroy(void* element) {
    if (element) {
        Logger* logger = (Logger*)element;
        Stack_Destroy(logger->info, String_Destroy);
        Stack_Destroy(logger->error, String_Destroy);
        free(element);
    }
}

void Logger_AppendInfo(Logger* logger, ...) {
    if (logger) {
        va_list list;
        va_start(list, logger);

        char* arg;
        String* str = String_Init();
        while ((arg = va_arg(list, char*)) != NULL) {
            char* newArg = malloc(sizeof(char) * strlen(arg) + 1);
            strcpy(newArg, arg);
            String_Append(str, newArg, NULL);
        }
        Stack_Push(logger->info, str);
        va_end(list);
    }
}

void Logger_AppendError(Logger* logger, ...) {
    if (logger) {
        va_list list;
        va_start(list, logger);

        char* arg;
        String* str = String_Init();
        while ((arg = va_arg(list, char*)) != NULL) {
            char* newArg = malloc(sizeof(char) * strlen(arg) + 1);
            strcpy(newArg, arg);
            String_Append(str, newArg, NULL);
        }
        Stack_Push(logger->error, str);
        va_end(list);
    }
}

void Logger_PrintInfo(Logger* logger) {
    Logger_Print(logger, "INFO", logger->info);
}

void Logger_PrintError(Logger* logger) {
    Logger_Print(logger, "ERROR", logger->error);
}