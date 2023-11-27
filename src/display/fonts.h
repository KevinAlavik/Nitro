#ifndef FONTS_H_
#define FONTS_H_

#include <stdint.h>

#define TEXT_PADDING    2
#define LETTER_WIDTH    8 
#define LETTER_HEIGHT   16
#define INDENT_AMOUNT   4

extern uint8_t vga_deafult[256][16];
extern uint8_t (*current_font)[16];

#endif // FONTS_H_
