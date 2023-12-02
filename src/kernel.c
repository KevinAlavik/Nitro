#include "serial/serial.h"
#include "serial/tools.h"
#include "display/vga.h"
#include "utilities/logger.h"
#include "cpu/cpu.h"
#include "idt/idt.h"
#include "memory/pm.h"
#include "nighterm/nighterm.h"
#include "egl/backends/fb.h"

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
    log(OK, "Initialized IDT.");
    printf("Welcome to ");
    nighterm_set_char_fg(102, 179, 255);
    printf("Nitro\n");
    nighterm_set_char_fg(255,255,255);

    hcf();
}