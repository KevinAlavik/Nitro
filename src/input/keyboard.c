#include "keyboard.h"
#include "layouts.h"
#include "utilities/printf.h"
#include "serial/serial.h"
#include "serial/tools.h"

#include "states/states.h"

#include <nighterm/nighterm.h>

struct Keyboard keyboard;

__attribute__((interrupt)) void keyboard_handler(void *)
{
    if (KEYBOARD_SUPPORT) {
        uint8_t data = inb8(PS2_DATA);

        if (keyboard.data != data) {
            keyboard.data = data;
        }

        //printf("Scancode: %u; String: %s\n", keyboard.data, sv_layout[keyboard.data].normal);

        char* letterString;

        if (keyboard.data == 0)
        {
            panic("Got invalid keyboard data.");
        }

        if (keyboard.data == 0x2A || keyboard.data == 0x36) { keyboard.state = KEYBOARD_SHIFT; }
        if (keyboard.data == 0x3A)                          { keyboard.state = KEYBOARD_CAPS; }
        if (keyboard.data == 0xAA || keyboard.data == 0xB6) { keyboard.state = KEYBOARD_NORMAL; }
        
        if (keyboard.data == 0x01) { 
            if (!keyboard.out) {
                #define ENABLE_KEYBOARD_PRINTF
                keyboard.out = true;
            } else {
                #define DISABLE_KEYBOARD_PRINTF
                keyboard.out = false;
            }
        }

        if (keyboard.data == 0x48) { nighterm_move_cursor(term.curY - 1, term.curX - 1); }
        if (keyboard.data == 0x50) { nighterm_move_cursor(term.curY + 1, term.curX - 1); }
        if (keyboard.data == 0x4B) { nighterm_move_cursor(term.curY, term.curX - 1); }
        if (keyboard.data == 0x4D) { nighterm_move_cursor(term.curY, term.curX + 1); }

        if (keyboard.state == KEYBOARD_NORMAL)     { letterString = sv_layout[data].normal; }
        else if (keyboard.state == KEYBOARD_SHIFT) { letterString = sv_layout[data].shifted; }
        else if (keyboard.state == KEYBOARD_CAPS)  { letterString = sv_layout[data].caps; }
        else {
            printf("Keyboard struct has weird state: %u", keyboard.state);
        }

        // TODO: Store old curor location and compare if its not the same if it isnt then clear the old loc

        if((KEYBOARD_PRINTF_SUPPORT || keyboard.out) && letterString != "") { 
            printf("%s", letterString);
        }


        i8259_SendEndOfInterrupt(1);
    }
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