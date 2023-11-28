#include "pm.h"
#include <limine.h>

struct limine_memmap_entry **unused_memory_entries = NULL;
uint64_t unused_memory_count = 0;

static volatile struct limine_memmap_request request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

//TODO: Fix tripple fault
void init_pm()
{
    if (request.response->entry_count > 0)
    {
        unused_memory_entries = request.response->entries;
        unused_memory_count = request.response->entry_count;
    }
    else
    {
        panic("Could not initialize pm. No memory map entries received.");
    }
}