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
#include "pit/pit.h"
#include "input/keyboard.h"
#include "errors/errors.h"

#define PSF2_MODE

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, .revision = 0};

// Kernel Variables
uint64_t usable_memory_count;
uint64_t screen_height;
uint64_t screen_width;

int saved_x;
int saved_y;

int log_mode = 0;

char* window_title = "Nighterm";

void panic(char* m) { 
    log(PANIC, m); 
    
    saved_x = term.curX;
    saved_y = term.curY;
    
    nighterm_move_cursor(term.rows - 2, 0);
    printf("i think something broke\n");
    
    nighterm_move_cursor(saved_y, saved_x);
    hcf(); 
}

void err(char* m) { 
    log(ERROR, m); 
    
    saved_x = term.curX;
    saved_y = term.curY;
    
    nighterm_move_cursor(term.rows - 2, 0);
    printf(":(\n");
    
    nighterm_move_cursor(saved_y, saved_x);
}

void ok(char* m) { log(OK, m); }
void warn(char* m) { log(WARNING, m); }
void info(char* m) { log(INFO, m); }

void setup() {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    nighterm_move_cursor(1, 0);
    if(log_mode) { log(OK, "Initialized display."); }
    idt_init();
    if(log_mode) { log(OK, "Initialized IDT."); }
    register_error_handlers();
    if(log_mode) { log(OK, "Registered errors."); }
    init_pm();
    if(log_mode) { log(OK, "Initialized physical memory manager."); }
    usable_memory_count = get_usable_memory_count();
    if(log_mode) { log(OK, "Saved usable memory count."); }
    screen_height = getScreenHeight();
    screen_width = getScreenWidth();
    if(log_mode) { log(OK, "Saved screen height and width."); }
    i8259_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);
    if(log_mode) { log(OK, "Initialized PIC controller."); }
    pit_init();
    if(log_mode) { log(OK, "Initialized PIT controller."); }
    init_keyboard();
    if(log_mode) { log(OK, "Initialized keyboard."); }

    saved_x = term.curX;
    saved_y = term.curY;

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

    nighterm_move_cursor(term.rows - term.rows, 3);
    printf(" %s ", window_title);

    nighterm_move_cursor(saved_y, saved_x);
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
    //nighterm_clear();
    nighterm_set_char_fg(102, 179, 255);

    printf("\n");
    printf("        /      _/./\n");
    printf("   ,-'    `-:.,-'/\n");
    printf("  > O )<)    _  (\n");
    printf("   `-._  _.:' `-.\\\n");
    printf("       `` \\;\n");
    printf("\n");
    nighterm_set_char_fg(255, 255, 255);
    
    printf("Usable memory \t");
    nighterm_set_char_fg(146, 255, 151);
    printf("%s\n", to_mb(usable_memory_count));
    nighterm_set_char_fg(255, 255, 255);

    printf("\n");
    hlt();
}
