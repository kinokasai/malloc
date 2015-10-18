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
    //info("Creating new block at %p", p);
    struct blk *blk = p;
    blk->alc = 0;
    blk->size = size;
    blk->next = NULL;
    blk->prev = NULL;
    blk->data = (void *)((uintptr_t) p + sizeof (struct blk));
    //info("blk data -> %p", blk->data);
    return blk;
}

struct blk *split_blk(struct blk *blk, size_t size)
{
    //info("Splitting blk at %p to size %zu", (void *) blk, size);
    if (size > blk->size)
        warn("Trying to split block in a bigger size");
    if (size + sizeof (struct blk) > blk->size)
    {
        warn("This is going to underflow");
        raise(SIGTRAP);
    }
    int fsize = blk->size - size - sizeof (struct blk);
    blk->size = size;
    void *ptr = (void *)((uintptr_t) blk + sizeof (struct blk) + blk->size);
    struct blk *nblk = create_blk(ptr, fsize);
    nblk->next = blk->next;
    blk->next = nblk;
    nblk->prev = blk;
    //info("Returning nblk -> %p with data -> %p", nblk, nblk->data);
    //info("nblk->next -> %p", nblk->next);
    return blk;
}

struct blk *next_blk(struct blk *blk, size_t size)
{
    if (!blk)
        warn("You shouldn't call next_blk with null");
    while (blk->next)
    {
        if (size + sizeof (struct blk) < blk->size && !blk->alc)
            return blk;
        blk = blk->next;
    }
    return blk;
}

static int merge_blk(struct blk *nblk, struct blk *oblk)
{
    nblk->size += sizeof (struct blk) + oblk->size;
    nblk->next = oblk->next;
    return nblk->size;
}

/* Returns the size of the new free'd block */
int free_blk(struct blk *blk)
{
    //info("free'ing blk -> %p", blk);
    blk->alc = 0;
    int size = blk->size;
    if (blk->next && !blk->next->alc)
        size = merge_blk(blk, blk->next);
    if (blk->prev && !blk->prev->alc)
        size = merge_blk(blk->prev, blk);
    return size;
}
