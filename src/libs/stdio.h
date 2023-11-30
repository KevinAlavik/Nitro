#ifndef STDIO_H_
#define STDIO_H_

#include "display/vga.h"
#include "display/fonts.h"

void printf(const char* text);
void printfc(const char* text, int r, int g, int b);
void printfcs(const char* text, int r, int g, int b, int size);
void printfs(const char* text, int size);
void print_char(char letter, int x, int y, int r, int g, int b, int fontSize);

#endif // STDIO_H_