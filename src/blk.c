#define _GNU_SOURCE
#include "blk.h"
#include "debug.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

static unsigned long align_page(size_t size)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long tmp = page_size;
    while (tmp < size + sizeof (struct blk))
        tmp += page_size;
    return tmp;
}

static size_t bms(size_t size)
{
    size_t blk_size = 0;
    while (blk_size < size)
        blk_size += sizeof (size_t);
    return blk_size;
}

struct blk *find_next(struct blk *blk, size_t size)
{
    while (blk->next && !(blk->alc == 0 && size > blk->size))
    {
        blk = blk->next;
    }
    return (blk->next == NULL && blk->size < size) ? NULL : blk;
}

/* blk should be the end block of the list */
struct blk *blk_pg(size_t size)
{
    size = align_page(size); 
    void *mptr = mmap(NULL, size, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mptr == MAP_FAILED)
    {
        info("MAP_FAILED!");
        errno = ENOMEM;
        return NULL;
    }
    else
    {
        info("Mapping %lu bytes of memory", size);
        info("Memory mapped at %p", mptr);
    }
    struct blk *nblk = mptr;
    nblk->alc = 1;
    nblk->size = bms(size);
    nblk->next = NULL;
    mptr = (void *) ((uintptr_t) mptr + sizeof (struct blk));
    nblk->data = mptr;
    return nblk;
}

/* size should be size_t aligned */
struct blk *alloc(struct blk *blk, size_t size)
{
    struct blk *tblk = find_next(blk, size);
    if (!tblk)
        tblk = blk_pg(size);
    info("Pointer arithmetic");
    void *ptr = tblk;
    ptr = (void *) ((uintptr_t) ptr + sizeof (struct blk) + tblk->size);
    struct blk *nblk = ptr;
    nblk->alc = 1;
    nblk->size = size;
    nblk->next = NULL;
    nblk->data = nblk + sizeof (struct blk);
    tblk->next = nblk;
    return nblk;
}
