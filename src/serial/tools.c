#include "tools.h"
#include "serial.h"

void serial_printf(uint16_t port, char* string) {

    int i = 0;
    while (string[i] != '\0') {
        outb8(port, string[i]);
        i++;
    }
    outb8(port, '\r');
    outb8(port, '\n');
}