#define _GNU_SOURCE
#include "malloc.h"
#include "errno.h"
#include "page.h"
#include "blk.h"
#include "help.h"
#include "debug.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>

/* FIXME Add -Werror flag */

void *malloc(size_t size)
{
    size = word_align(size);
    if (size == 0)
        return NULL;
    static struct page *page = NULL;
    if (!page)
        page = create_page(size);
    else
    return page->fblk;
}



















/*static struct blk *init(size_t size)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    void *mptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (mptr == MAP_FAILED)
    {
        info("MAP_FAILED!");
        errno = ENOMEM;
        return NULL;
    }
    else
    {
        info("Mapping %lu bytes of memory", page_size);
        info("Memory mapped at %p", mptr);
    }
    struct blk *blk = mptr;
    blk->alc = 1;
    blk->size = bms(size);
    blk->next = NULL;
    Apparently, you should add +1 here.
    mptr = (void *) ((uintptr_t) mptr + sizeof (struct blk));
    blk->data = mptr;
    return blk;
}*/

/*
** Warning: Be wary of size overflows
** when you add sizeof (struct blk)
*/
/*void *malloc(size_t size)
{
    info("malloc'ing %zu bytes", size);
    size = bms(size);
    info("who are really %zu aligned bytes", size);
    if (!size)
    {
        info("Returning NULL");
        return NULL;
    }
    static struct blk *blk = NULL;
    struct blk *cblk = NULL;
    if (!blk)
    {
        blk = blk_pg(size);
        cblk = blk;
    }
    else
        cblk = alloc(blk, bms(size) + sizeof(struct blk));
    if (!cblk)
    {
        info("Returning NULL");
        return NULL;
    }
    info("Returning %lu bytes at %p", cblk->size, cblk->data);
    print_mem(blk);
    return cblk->data;
}

void free(void *ptr)
{
    return;
}*/
