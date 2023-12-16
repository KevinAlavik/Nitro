#ifndef VGA_H_
#define VGA_H_

#include <stdint.h>
#include <stddef.h>
#include <limine.h>

void init_display();
void display_write_data(uint32_t address, uint8_t red, uint8_t green, uint8_t blue);
unsigned int rgb(uint8_t red, uint8_t green, uint8_t blue);
void draw_pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t b, uint8_t g);
void set_background_color(uint16_t red, uint16_t green, uint16_t blue);
int getScreenWidth();
int getScreenHeight();
struct limine_framebuffer *getFb();

#endif // VGA_H_