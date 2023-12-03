#ifndef PM_H
#define PM_H

#include <stdint.h>
#include <stddef.h> 
#include <limine.h>

extern struct limine_memmap_entry** physical_memory_entires;

void init_pm();
uint64_t get_usable_memory_count();

#endif