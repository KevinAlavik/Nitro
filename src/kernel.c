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
#include "states/states.h"

#define ENABLE_LOG_STARTUP_TASKS
#define ENABLE_KEYBOARD
#define ENABLE_KEYBOARD_PRINTF

#define PSF2_MODE

static volatile struct limine_module_request mod_request = {
    .id = LIMINE_MODULE_REQUEST, .revision = 0};

// Kernel Variables
uint64_t usable_memory_count;
uint64_t screen_height;
uint64_t screen_width;

int saved_x;
int saved_y;

char* window_title = "Nighterm";

void panic(char* m) { 
    log(PANIC, m);
    hcf(); 
}

void err(char* m) { 
    log(ERROR, m);
}

void ok(char* m) { log(OK, m); }
void warn(char* m) { log(WARNING, m); }
void info(char* m) { log(INFO, m); }

char* to_mb(uint64_t size) {
    static char result[20]; // Adjust the size based on your needs
    uint64_t size_in_mb = size / (1024 * 1024);
    uint64_t fractional_part = (size % (1024 * 1024)) * 1000 / (1024 * 1024);

    snprintf(result, sizeof(result), "%lu.%03lu MB", size_in_mb, fractional_part);
    return result;
}

void setup() {
    init_display();
    init_nighterm(mod_request.response->modules[0]);
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized display."); }
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized Nighterm."); }
    idt_init();
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized IDT."); }
    register_error_handlers();
    if(LOG_TASKS_SUPPORT) { log(OK, "Registered errors."); }
    init_pm();
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized physical memory manager."); }
    usable_memory_count = get_usable_memory_count();
    if(LOG_TASKS_SUPPORT) { log(OK, "Saved usable memory count."); }
    screen_height = getScreenHeight();
    screen_width = getScreenWidth();
    if(LOG_TASKS_SUPPORT) { log(OK, "Saved screen height and width."); }
    i8259_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized PIC controller."); }
    pit_init();
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized PIT controller."); }
    init_keyboard();
    if(LOG_TASKS_SUPPORT) { log(OK, "Initialized keyboard."); }
    log(WARNING, "Booting into pre-boot, unstable."); 
}

void _start(void) {
    setup();
    nighterm_set_char_fg(132, 132, 130);
    printf("\npre-boot env\n-------------------------------\n");
    nighterm_set_char_fg(255, 255, 255);

    printf("Usable memory \t");
    nighterm_set_char_fg(146, 255, 151);
    printf("%s\n", to_mb(usable_memory_count));
    nighterm_set_char_fg(255, 255, 255);

    printf("Terminal Cols \t");
    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", term.cols);
    nighterm_set_char_fg(255, 255, 255);
    
    printf("Terminal Rows \t");
    nighterm_set_char_fg(146, 255, 151);
    printf("%u\n", term.rows);
    nighterm_set_char_fg(255, 255, 255);
    
    printf("Terminal \t\t");
    nighterm_set_char_fg(146, 255, 151);
    printf("%s\n", term.title);
    nighterm_set_char_fg(255, 255, 255);
    nighterm_set_char_fg(132, 132, 130);
    printf("-------------------------------\n");
    nighterm_set_char_fg(255, 255, 255);
    hlt();
}
