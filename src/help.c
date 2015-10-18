#include "help.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>

unsigned long page_align(size_t size)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long tmp = page_size;
    tmp += size / tmp * page_size;
    return tmp;
}

size_t word_align(size_t size)
{
    size_t tsize = sizeof (size_t);
    return (size - 1) / tsize * tsize + tsize;
}

void print_blk(struct blk *blk)
{
    if (blk->alc > 1 || blk->size > 100000000000)
        raise(SIGTRAP);
    fprintf(stderr, "- BLK -> %p\n", (void *) blk);
    fprintf(stderr, "  - alc'd: %d\n", blk->alc);
    fprintf(stderr, "  - Size: %zu\n", blk->size);
    fprintf(stderr, "  - Next: %p\n", (void *) blk->next);
    fprintf(stderr, "  - Prev: %p\n", (void *) blk->prev);
    fprintf(stderr, "  - Data: %p\n", (void *) (blk + 1));
}

static void print_page(struct page *page)
{
    fprintf(stderr, "PAGE -> %p to %p\n", (void *) page,
           (void *) ((uintptr_t) page + page->size));
    fprintf(stderr, "- Size: %zu\n", page->size);
    fprintf(stderr, "- Free size: %zu\n", page->free_size);
    fprintf(stderr, "- Next: %p\n", (void *) page->next);
    fprintf(stderr, "- Prev: %p\n", (void *) page->prev);
    struct blk *blk = page->fblk;
    while (blk)
    {
        print_blk(blk);
        blk = blk->next;
    }
}

void print_mem(struct page *page)
{
    if (!page)
        fprintf(stderr, "No memory mapped\n");
    while (page)
    {
        print_page(page);
        page = page->next;
    }
}

