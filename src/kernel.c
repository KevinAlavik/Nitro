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

__attribute__((interrupt)) void division_by_zero_error(void*) {
    log(ERROR, "Division by zero!");
}

void init_os_interupts() {
    set_idt_gate(0, (uint64_t)&division_by_zero_error, 0x28, 0x8E);
}

void _start(void) {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    log(OK, "Initialized display.");
    idt_init();
    log(OK, "Initialized IDT.");
    init_os_interupts();
    log(OK, "Initialized os interupts.");
    init_pm();
    log(OK, "Initialized physical memory manager.");
    
    printf("\n");
    printf("Welcome to ");
    nighterm_set_char_fg(102, 179, 255);
    printf("Nitro\n");
    nighterm_set_char_fg(255,255,255);
    
    hcf();
}