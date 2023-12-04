#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define PS2_COMMAND 0x64
#define PS2_DATA 0x60

#define KEYBOARD_NORMAL 0
#define KEYBOARD_SHIFT 1
#define KEYBOARD_CAPS 2

struct Keyboard {
    uint8_t state;
};
extern struct Keyboard keyboard;


void init_keyboard();

#endif /* KEYBOARD_H */
