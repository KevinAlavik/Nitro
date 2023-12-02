#include "ps2.h"
#include <idt/idt.h>
#include <ktools/pic.h>
#include <display/vga.h>
#include <utilities/printf.h>

#define PS2_COMMAND 0x64
#define PS2_DATA 0x60

char buffer[3];
char offset;
char buttons;

__attribute__((interrupt)) void mus_handler(void *)
{
        uint8_t status = inb8(PS2_COMMAND);
        if (!(status & 0x20))
             i8259_SendEndOfInterrupt(1);

        buffer[offset] = inb8(PS2_DATA);
        
        offset = (offset + 1) % 3;

        if(offset == 0)
        {
            if(buffer[1] != 0 || buffer[2] != 0)
            {
                draw_pixel(200 + buffer[1],200 + buffer[2],255,0,0);//mouse move
            }

            for(uint8_t i = 0; i < 3; i++)
            {
                if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
                {
                    if(buttons & (0x1<<i))
                        draw_pixel(0,0,255,0,0);//mouse move
                    else
                        draw_pixel(0,0,0,0,255);//mouse move
                }
            }
            buttons = buffer[0];
        }
    printf("a");
    i8259_SendEndOfInterrupt(0x0C);
}
__attribute__((interrupt)) void kb_handler(void *)
{

    char butt = inb8(PS2_DATA);
    printf("a");

    i8259_SendEndOfInterrupt(1);
}

void init_ps2()
{

    set_idt_gate(PIC_REMAP_OFFSET + 0x0C, (uint64_t)&mus_handler, 0x28, 0x8E);
    set_idt_gate(PIC_REMAP_OFFSET + 1, (uint64_t)&kb_handler, 0x28, 0x8E);

    if (inb8(PS2_COMMAND) & 0x1)
        inb8(PS2_DATA);

    outb8(PS2_COMMAND, 0xAE);
    outb8(PS2_COMMAND, 0xA8);

    outb8(PS2_COMMAND, 0x60);
    outb8(PS2_DATA, 0b01000111);

    outb8(PS2_COMMAND, 0xD4);
    outb8(PS2_DATA, 0xFF);
    outb8(PS2_COMMAND, 0xD2);
    outb8(PS2_DATA, 0xFF);
    outb8(PS2_COMMAND, 0xD4);
    outb8(PS2_DATA, 0xF4);
    outb8(PS2_COMMAND, 0xD2);
    outb8(PS2_DATA, 0xF4);
    i8259_Unmask(0xC);
    i8259_Unmask(1);
}
