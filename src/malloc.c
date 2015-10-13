#define _GNU_SOURCE
#include "malloc.h"
#include "errno.h"
#include "debug.h"
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>

void *malloc(size_t size)
{
    info("Trying to map %lu bytes of  memory", size);
    long page_size = sysconf(_SC_PAGESIZE);
    unsigned long mps = page_size;
    while (size >= mps)
        mps += page_size;
    info("Mapping %lu bytes of memory", mps);
    void *mptr = mmap(NULL, mps, PROT_READ | PROT_WRITE,
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
