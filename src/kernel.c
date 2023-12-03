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

// Kernel Variables
uint64_t usable_memory_count;
uint64_t screen_height;
uint64_t screen_width;


void setup() {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    log(OK, "Initialized display.");
    idt_init();
    log(OK, "Initialized IDT.");
    init_pm();
    log(OK, "Initialized physical memory manager.");
    usable_memory_count = get_usable_memory_count();
    log(OK, "Saved usable memory count.");
    screen_height = getScreenHeight();
    screen_width = getScreenWidth();
    log(OK, "Saved screen height and width.");
}

void _start(void) {
    setup();
    nighterm_set_char_fg(102, 179, 255);
    printf("\n");
    printf("        /      _/./\n");
    printf("   ,-'    `-:.,-'/\n");
    printf("  > O )<)    _  (\n");
    printf("   `-._  _.:' `-.\\\n");
    printf("       `` \\;\n");
    printf("\n");

    nighterm_set_char_fg(255, 255, 255);
    printf("Usable memory: %u\n", usable_memory_count);
    printf("Screen height: %u\n", screen_height);
    printf("Screen width:  %u\n", screen_width);
    printf("Terminal rows: %u\n", term.rows);
    printf("Terminal cols: %u\n", term.cols);
    hcf();
}