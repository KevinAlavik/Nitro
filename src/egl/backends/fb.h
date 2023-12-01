#ifndef __FB_H__
#define __FB_H__
#include <stdint.h>

void draw_line(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2, uint8_t r, uint8_t g, uint8_t b);
void draw_rect(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint8_t r, uint8_t g, uint8_t b, int filled);
void draw_circle(uint64_t centerX, uint64_t centerY, uint64_t radius, uint8_t r, uint8_t g, uint8_t b, int filled);
void draw_text(char* text,int _x, int _y, uint8_t r, uint8_t g, uint8_t b);

#endif // __FB_H__