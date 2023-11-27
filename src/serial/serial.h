#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>

#define QEMU_SERIAL_PORT 0x3f8

void outb8(uint16_t port,uint8_t value);
void outb16(uint16_t port,uint16_t value);
void outb32(uint16_t port,uint32_t value);
uint8_t inb8(uint16_t port);
uint16_t inb16(uint16_t port);
uint32_t inb32(uint16_t port);
void iowait();

#endif // SERIAL_H_