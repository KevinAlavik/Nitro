#ifndef PM_H
#define PM_H

#include <stdint.h>
#include <stddef.h> 
#include <limine.h>

extern struct limine_memmap_entry** physical_memory_entires;
extern uint64_t usable_memory_count;

void init_pm();

#endif
