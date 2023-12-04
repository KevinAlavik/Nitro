#include <stdbool.h>
#include "serial/serial.h"
#include "serial/tools.h"
#include "display/vga.h"
#include "utilities/logger.h"
#include "cpu/cpu.h"
#include "idt/idt.h"
#include "memory/pm.h"
#include "nighterm/nighterm.h"
#include "egl/backends/fb.h"
#include "pic/controller.h"
#include "input/keyboard.h"

#include <inttypes.h>

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, .revision = 0};

void panic(char* m) { log(PANIC, m); hlt(); }

void err(char* m) { log(ERROR, m); }

// Kernel Variables
uint64_t usable_memory_count;
uint64_t screen_height;
uint64_t screen_width;

void setup() {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    nighterm_move_cursor(1, 0);
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
    i8259_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);
    log(OK, "Initialized PIC controller.");
    init_keyboard();
    log(OK, "Initialized keyboard.");
}

char* to_mb(uint64_t size) {
    static char result[20]; // Adjust the size based on your needs
    uint64_t size_in_mb = size / (1024 * 1024);
    uint64_t fractional_part = (size % (1024 * 1024)) * 1000 / (1024 * 1024);

    snprintf(result, sizeof(result), "%lu.%03lu MB", size_in_mb, fractional_part);
    return result;
}

__attribute__((interrupt)) void test_int(void*) {
    log(OK, "Interupt called");
}

void _start(void) {
    setup();
    nighterm_clear();
    nighterm_set_char_fg(102, 179, 255);

    printf("\n");
    printf("        /      _/./\n");
    printf("   ,-'    `-:.,-'/\n");
    printf("  > O )<)    _  (\n");
    printf("   `-._  _.:' `-.\\\n");
    printf("       `` \\;\n");
    printf("\n");
    nighterm_set_char_fg(255, 255, 255);
    
    printf("Usable memory --- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("%s\n", to_mb(usable_memory_count));
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Screen height --- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", screen_height);
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Screen width ---- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", screen_width);
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Terminal rows --- ");

    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", term.rows);
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Terminal cols --- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", term.cols);
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Terminal -------- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("Nighterm\n", term.cols);
    nighterm_set_char_fg(255, 255, 255);


    nighterm_set_char_fg(255, 255, 255);
    printf("Layout ---------- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("SE-SV\n", term.cols);
    nighterm_set_char_fg(255, 255, 255);

    nighterm_set_char_fg(255, 255, 255);
    printf("Keyboard -------- ");
    nighterm_set_char_fg(146, 255, 151);
    printf("PS/2\n", term.cols);
    nighterm_set_char_fg(255, 255, 255);

    // Borders
    nighterm_move_cursor(term.rows - 1, 0);
    for (int i = 0; i < term.cols; i++) {
        nighterm_set_char_fg(122, 122, 122);
        printf("=");
    }

    nighterm_move_cursor(term.rows - term.rows, 0);
    for (int i = 0; i < term.cols; i++) {
        nighterm_set_char_fg(122, 122, 122);
        printf("=");
    }

    // Footer text

    nighterm_set_char_fg(255, 255, 255);
    nighterm_move_cursor(term.rows - 2, 0);
    printf(":)\n");

    hcf();
}
