#define _GNU_SOURCE
#include "blk.h"
#include "debug.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>

struct blk *create_blk(void *p, size_t size)
{
    struct blk *blk = p;
    blk->alc = 0;
    blk->size = size;
    blk->next = NULL;
    blk->prev = NULL;
    return blk;
}

struct blk *split_blk(struct blk *blk, size_t size)
{
    if (size > blk->size)
    {
        raise(SIGTRAP);
    }
    int fsize = blk->size - size;
    blk->size = size - sizeof (struct blk);
    void *ptr = (void *)((uintptr_t) blk + sizeof (struct blk) + blk->size);
    struct blk *nblk = create_blk(ptr, fsize);
    nblk->next = blk->next;
    blk->next = nblk;
    nblk->prev = blk;
    return blk;
}

struct blk *next_blk(struct blk *blk, size_t size)
{
    while (blk)
    {
        if (size < blk->size && !blk->alc)
            return blk;
        blk = blk->next;
    }
    return blk;
}

static int merge_blk(struct blk *nblk, struct blk *oblk)
{
    nblk->size += sizeof (struct blk) + oblk->size;
    if (oblk->next)
        oblk->next->prev = nblk;
    nblk->next = oblk->next;
    return nblk->size;
}

/* Returns the size of the new free'd block */
int free_blk(struct blk *blk)
{
    blk->alc = 0;
    int size = blk->size;
    if (blk->next && !blk->next->alc)
        size = merge_blk(blk, blk->next);
    if (blk->prev && !blk->prev->alc)
        size = merge_blk(blk->prev, blk);
    return size;
}
