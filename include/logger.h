#ifndef LOGGER_H
#define LOGGER_H

#include "stack.h"
#include "struct_definitions.h"

struct Logger {
    Stack* info; // struct String
    Stack* error; // struct String
};

Logger* Logger_Init(void);
void Logger_Destroy(void* element);

void Logger_AppendInfo(Logger* logger, ...);
void Logger_AppendError(Logger* logger, ...);

void Logger_PrintInfo(Logger* logger);
void Logger_PrintError(Logger* logger);

#endif