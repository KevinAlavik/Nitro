#include "keyboard.h"
#include "layouts.h"
#include "utilities/printf.h"
#include "serial/serial.h"
#include "serial/tools.h"


__attribute__((interrupt)) void keyboard_handler(void *)
{
    uint8_t data = inb8(PS2_DATA);

    if (data == 0)
    {
         panic("Got invalid keyboard data.");
    }

    if (sv_layout[data].normal != "")
    {
        char *letterString = sv_layout[data].normal;
        printf(letterString);
    }


    i8259_SendEndOfInterrupt(1);
}

void init_keyboard() {

    set_idt_gate(0x21, (uint64_t)&keyboard_handler, 0x28, 0x8E);

    if (inb8(PS2_COMMAND) & 0x1)
        inb8(PS2_DATA);
    outb8(PS2_COMMAND, 0x60);
    outb8(PS2_DATA, 0b01100111);

    outb8(PS2_COMMAND, 0xAE);
    outb8(PS2_DATA, 0xf4);
    i8259_Unmask(1);
}