#ifndef LOGGER_H_
#define LOGGER_H_

#include <nighterm/nighterm.h>
#include "printf.h"

typedef enum {
    INFO,
    WARNING,
    ERROR,
    PANIC,
    OK,
    CUSTOM
} LogLevel;

void log(LogLevel level, const char* message) {
    const char* level_str;
    int r, g, b;

    switch (level) {
        case INFO:
            level_str = "Info";
            r = 0; g = 0; b = 255;
            break;
        case WARNING:
            level_str = "Warning";
            r = 255; g = 165; b = 0;
            break;
        case ERROR:
            level_str = "Error";
            r = 255; g = 0; b = 0;
            break;
        case PANIC:
            level_str = "Panic";
            r = 255; g = 0; b = 0;
            break;
        case OK:
            level_str = "Ok";
            r = 0; g = 255; b = 0;
            break;
        default:
            level_str = "Unknown";
            r = g = b = 255;
            break;
    }
    printf("[ ");
    nighterm_set_char_fg(r,g,b);
    printf(level_str);
    nighterm_set_char_fg(255,255,255);
    printf(" ] %s\n", message);
}

void clog(const char* message, const char* custom_level_str, int custom_rgb[3]) {
    int r, g, b;
    const char* level_str = custom_level_str ? custom_level_str : "Custom";
    r = custom_rgb ? custom_rgb[0] : 255;
    g = custom_rgb ? custom_rgb[1] : 255;
    b = custom_rgb ? custom_rgb[2] : 255;

    printf("[ ");
    nighterm_set_char_fg(r,g,b);
    printf(level_str);
    nighterm_set_char_fg(255,255,255);
    printf(" ] %s\n", message);
}

#endif // LOGGER_H_
