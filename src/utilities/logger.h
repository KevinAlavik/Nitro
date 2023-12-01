#ifndef LOGGER_H_
#define LOGGER_H_

#include <nighterm/nighterm.h>
#include "printf.h"

typedef enum {
    INFO,
    WARNING,
    ERROR,
    PANIC,
    OK
} LogLevel;

void log(LogLevel level, const char* message) {
    const char* level_str;
    int r, g, b;

    switch (level) {
        case INFO:
            level_str = "INFO";
            r = 0; g = 0; b = 255; // Blue
            break;
        case WARNING:
            level_str = "WARNING";
            r = 255; g = 165; b = 0; // Orange
            break;
        case ERROR:
            level_str = "ERROR";
            r = 255; g = 0; b = 0; // Red
            break;
        case PANIC:
            level_str = "PANIC";
            r = 255; g = 0; b = 0; // Red
            break;
        case OK:
            level_str = "OK";
            r = 0; g = 255; b = 0; // Green
            break;
        default:
            level_str = "UNKNOWN";
            r = g = b = 255; // Default color
            break;
    }

    printf("[ ");
    nighterm_set_char_fg(r,g,b);
    printf(level_str);
    nighterm_set_char_fg(255,255,255);//NOTE: this is kinda wrong, look here if the color is misteriously resetting
    printf(" ] ");
    printf("%s\n",message);
}

#endif // LOGGER_H_
