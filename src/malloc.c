#define _GNU_SOURCE
#include "malloc.h"
#include <sys/mman.h>
#include "errno.h"
#include "debug.h"

void *malloc(size_t size)
{
    info("Trying to map %lu memory", size);
    void *mptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);
    if (mptr == NULL)
        errno = ENOMEM;
    info("Memory mapped at %p", mptr);
    return mptr;
}

void lol(void)
{
    return;
}

void free(void *ptr)
{
    return;
}
