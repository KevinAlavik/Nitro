#include "pm.h"
#include <limine.h>

struct limine_memmap_entry **physical_memory_entires = NULL;
uint64_t usable_memory_count = 0;

static volatile struct limine_memmap_request request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

void init_pm()
{
    if (request.response->entry_count > 0)
    {
        physical_memory_entires = request.response->entries;

        usable_memory_count = 0;
        for (uint64_t i = 0; i < request.response->entry_count; ++i)
        {
            if (physical_memory_entires[i]->type == LIMINE_MEMMAP_USABLE)
            {
                usable_memory_count += physical_memory_entires[i]->length;
            }
        }

        if (usable_memory_count <= 0)
        {
            panic("No usable memory found, something went wrong");
        }
    }
    else
    {
        panic("Could not initialize pm. No memory map entries received.");
    }
}

