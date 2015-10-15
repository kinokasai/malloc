#define _GNU_SOURCE
#include "malloc.h"
#include "errno.h"
#include "blk.h"
#include "debug.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>


static size_t bms(size_t size)
{
    size_t blk_size = 0;
    while (blk_size < size)
        blk_size += sizeof (size_t);
    return blk_size;
}

static struct blk *init(size_t size)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    void *mptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (mptr == MAP_FAILED)
    {
        info("MAP_FAILED!");
        errno = ENOMEM;
    }
    else
    {
        info("Mapping %lu bytes of memory", page_size);
        info("Memory mapped at %p", mptr);
    }
    struct blk *blk = mptr;
    blk->state = 1;
    blk->size = bms(size);
    blk->next = NULL;
    /* Apparently, you should add +1 here. */
    mptr = (void *) ((uintptr_t) mptr + sizeof (struct blk));
    blk->data = mptr;
    return blk;
}

void *malloc(size_t size)
{
    static struct blk *blk = NULL;
    struct blk *cblk = NULL;
    if (!blk)
    {
        blk = init(size);
        cblk = blk;
    }
    else
        cblk = alloc(blk, bms(size));
    info("Returning %lu bytes at %p", cblk->size, cblk->data);
    return cblk->data;
}

void free(void *ptr)
{
    return;
}
