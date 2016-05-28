#ifndef LOGGING_H
#define LOGGING_H

enum levels {
    ERROR,
    INFO,
    WARN,
    DEBUG
} log_level;

void log_print(int, char*, ...);

#endif