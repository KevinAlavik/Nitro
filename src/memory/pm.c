#include "pm.h"
#include <limine.h>

struct limine_memmap_entry **physical_memory_entries = NULL;

static volatile struct limine_memmap_request request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void init_pm()
{
    if (request.response->entry_count > 0)
    {
        physical_memory_entries = request.response->entries;
    }
    else
    {
        panic("Could not initialize pm. No memory map entries received.");
    }
}

uint64_t get_usable_memory_count()
{
    if (physical_memory_entries == NULL)
    {
        // If init_pm hasn't been called yet, you might want to call it here.
        // init_pm();
        panic("Memory map not initialized. Call init_pm before get_usable_memory_count.");
    }

    uint64_t usable_memory_count = 0;
    for (uint64_t i = 0; i < request.response->entry_count; ++i)
    {
        if (physical_memory_entries[i]->type == LIMINE_MEMMAP_USABLE)
        {
            usable_memory_count += physical_memory_entries[i]->length;
        }
    }

    return usable_memory_count;
}
