#define _GNU_SOURCE
#include "malloc.h"
#include <sys/mman.h>
#include "errno.h"
#include "debug.h"

void *malloc(size_t size)
{
    info("Trying to map %lu bytes of  memory", size);
    void *mptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (mptr == MAP_FAILED)
    {
        info("MAP_FAILED!");
        errno = ENOMEM;
    }
    else
        info("Memory mapped at %p", mptr);
    return mptr;
}

void free(void *ptr)
{
    return;
}
