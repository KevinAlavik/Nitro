#include "keyboard.h"
#include "layouts.h"
#include "utilities/printf.h"
#include "serial/serial.h"
#include "serial/tools.h"

struct Keyboard keyboard;

__attribute__((interrupt)) void keyboard_handler(void *)
{
    uint8_t data = inb8(PS2_DATA);
    char* letterString;

    //printf("Got keyboard data: %u. String: %s\n", data, sv_layout[data].normal);

    if (data == 0)
    {
        panic("Got invalid keyboard data.");
    }

    if (data == 0x2A || data == 0x36) { keyboard.state = KEYBOARD_SHIFT; }
    if (data == 0x3A) { keyboard.state = KEYBOARD_CAPS; }
    if (data == 0x80) { keyboard.state = KEYBOARD_NORMAL; }
    
    if (keyboard.state == KEYBOARD_NORMAL) { letterString = sv_layout[data].normal; }
    else if (keyboard.state == KEYBOARD_SHIFT) { letterString = sv_layout[data].shifted; }
    else if (keyboard.state == KEYBOARD_CAPS) { letterString = sv_layout[data].caps; }
    else {
        printf("Keyboard struct has weird state: %u", keyboard.state);
    }

    if (letterString != "")
    {
        printf(letterString);
    }

    i8259_SendEndOfInterrupt(1);
}

void init_keyboard()
{
    keyboard.state = KEYBOARD_NORMAL;

    set_idt_gate(0x21, (uint64_t)&keyboard_handler, 0x28, 0x8E);

    if (inb8(PS2_COMMAND) & 0x1)
        inb8(PS2_DATA);
    outb8(PS2_COMMAND, 0x60);
    outb8(PS2_DATA, 0b01100111);

    outb8(PS2_COMMAND, 0xAE);
    outb8(PS2_DATA, 0xf4);
    i8259_Unmask(1);
}