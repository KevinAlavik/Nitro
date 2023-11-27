#include "serial.h"

#define UNUSED 0x80

void iowait() { outb8(UNUSED, 0); }

void outb8(uint16_t port, uint8_t value) {
    __asm__ volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

void outb16(uint16_t port, uint16_t value) {
    __asm__ volatile("outw %1, %0" : : "dN"(port), "a"(value));
}

void outb32(uint16_t port, uint32_t value) {
    __asm__ volatile("outl %1, %0" : : "dN"(port), "a"(value));
}

uint8_t inb8(uint16_t port) {
    uint8_t r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "dN"(port));
    return r;
}

uint16_t inb16(uint16_t port) {
    uint16_t r;
    __asm__ volatile("inw %1, %0" : "=a"(r) : "dN"(port));
    return r;
}

uint32_t inb32(uint16_t port) {
    uint32_t r;
    __asm__ volatile("inl %1, %0" : "=a"(r) : "dN"(port));
    return r;
}