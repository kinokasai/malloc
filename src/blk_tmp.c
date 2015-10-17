#define _GNU_SOURCE
#include "blk.h"
#include "debug.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

struct blk *create_blk(void *p, size_t size)
{
    struct blk *blk = p;
    blk->alc = 0;
    blk->size = size;
    blk->data = (void *)((uintptr_t) p + sizeof (struct blk));
    return blk;
}































































/*static void print_blk(struct blk *blk)
{
    printf("BLK %p\n", blk);
    printf("Alloc'd: %d\n", blk->alc);
    printf("Data ptr -> %p\n", blk->data);
    printf("Next blk -> %p\n", blk->next);
}

void print_mem(struct blk *blk)
{
    if (!blk)
        return;
    while (blk->next)
    {
        print_blk(blk);
        blk = blk->next;
    }
}

struct blk *find_next(struct blk *blk, size_t size, int *remap)
{
    while (blk->next && !(blk->alc == 0 && size > blk->size))
    {
        blk = blk->next;
    }
    if (!blk->next && size > blk->size)
        *remap = 1;
    return blk;
}

struct blk *blk_pg(size_t size)
{
    info("Trying to mmap %zu bytes", size);
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
        info("Mapping %zu bytes of memory", size);
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

struct blk *alloc(struct blk *blk, size_t size)
{
    int remap = 0;
    struct blk *tblk = find_next(blk, size, &remap);
    struct blk *nblk = NULL;
    if (remap)
        nblk = blk_pg(size);
    if (!tblk)
    {
        info("tblk null");
        return NULL;
    }
    void *ptr = tblk;
    if (!remap)
    {
        ptr = (void *) ((uintptr_t) ptr + sizeof (struct blk) + tblk->size);
        struct blk *nblk = ptr;
        nblk->alc = 1;
        nblk->size = size;
        nblk->next = NULL;
        nblk->data = nblk + sizeof (struct blk);
    }
    tblk->next = nblk;
    ptr = (void *) ((uintptr_t) ptr + sizeof (struct blk) + nblk->size);
    struct blk *fblk = ptr;
    fblk->alc = 0;
    return nblk;
}*/
