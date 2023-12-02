#include "serial/tools.h"
#include "display/vga.h"
#include "utilities/logger.h"
#include "input/ps2.h"
#include "cpu/cpu.h"
#include "idt/idt.h"
#include "memory/pm.h"
#include "nighterm/nighterm.h"
#include "egl/backends/fb.h"
#include <ktools/pic.h>

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, .revision = 0};

void panic(char* m) {
    log(PANIC, m);
    hlt();
}

void _start(void) {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    log(OK, "Initialized display.");
    idt_init();
    i8259_Configure(PIC_REMAP_OFFSET,PIC_REMAP_OFFSET,false);
    log(OK, "Initialized IDT.");

    init_ps2();
    printf("Welcome to ");
    nighterm_set_char_fg(102, 179, 255);
    printf("Nitro\n");
    nighterm_set_char_fg(255,255,255);//NOTE: this is kinda wrong, look here if the color is misteriously resetting

    printf("Hello World!");

    draw_rect(100,100,200,100,255,255,255,1);
    draw_text("\"\"Button\"\"",120,75,255,0,0);

    hcf();
}