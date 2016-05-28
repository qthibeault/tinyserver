#include <stdio.h>
#include <stdarg.h>

#include "logging.h"

#define ANSI_COLOR_BASE 31
#define ANSI_RESET "\x1b[0m"

void log_print(int level, char *msg, ...)
{
    char *levels[] = { "ERROR", "INFO", "WARN", "DEBUG" };
    printf("[\x1b[%dm %s %s]: ", ANSI_COLOR_BASE + level, levels[level], ANSI_RESET); 
    
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    
    printf("\n");
}