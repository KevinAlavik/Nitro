// Serial Imports
#include "serial/serial.h"
#include "serial/tools.h"

// VGA Imports
#include "display/vga.h"

// CPU Imports
#include "cpu/cpu.h"

// Utilities Imports
#include "utilities/logger.h"

// IDT Imports
#include "idt/idt.h"

void _start(void) {
    init_display();
    set_background_color(0, 0, 0);
    log(OK, "Initialized display.");
    idt_init();
    log(OK, "Initialized IDT manager.");

    printf("Welcome to ");
    printfc("Nitro\n", 102, 179, 255);
    
    hcf();
}
