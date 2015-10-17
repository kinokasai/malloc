#include "help.h"
#include <unistd.h>
#include <stdio.h>
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

static void print_blk(struct blk *blk)
{
    printf("- BLK -> %p\n", (void *) blk);
    printf("  - alc'd: %d\n", blk->alc);
    printf("  - Size: %zu\n", blk->size);
    printf("  - Next: %p\n", (void *) blk->next);
    printf("  - Prev: %p\n", (void *) blk->prev);
    printf("  - Data: %p\n", (void *) blk->data);
}

static void print_page(struct page *page)
{
    printf("PAGE -> %p to %p\n", (void *) page,
           (void *) ((uintptr_t) page + page->size));
    printf("- Size: %zu\n", page->size);
    printf("- Free size: %zu\n", page->free_size);
    printf("- Next: %p\n", (void *) page->next);
    printf("- Prev: %p\n", (void *) page->prev);
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
        printf("No memory mapped\n");
    while (page)
    {
        print_page(page);
        page = page->next;
    }
}

