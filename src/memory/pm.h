#ifndef PM_H
#define PM_H

#include <stdint.h>
#include <stddef.h> 
#include <limine.h>

extern struct limine_memmap_entry** unused_memory_entries;
extern uint64_t unused_memory_count;

void init_pm();

#endif
