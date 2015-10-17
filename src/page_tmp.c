#define _GNU_SOURCE
#include "page.h"
#include "debug.h"
#include "help.h"
#include "blk.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

/* Checks for the next page capable of containing size */
/* Size may need to be aligned */
struct page *page_next(struct page *page, size_t size)
{
    if (!page)
    {
        info("This shouldn't happen, I can't find any page");
        return NULL;
    }
    while (page->next)
    {
        if (page->free_size < size)
            return page;
        page = page->next;
    }
    return page;
}

struct page *create_page(size_t size)
{
    info("Trying to mmap page of %zu bytes", size);
    unsigned long page_size = page_align(size);
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
    struct page *page = mptr;
    page->next = NULL;
    page->fblk = NULL;
    page->size = page_size;
    page->free_size = page_size - sizeof (struct page) - sizeof (struct blk);
    page->fblk = create_blk(page->fblk, size);
    info("Returning page at %p of size %zu", page, page->size);
    return page;
}

/* This should take the first page of the list */
struct page *add_blk(struct page *page, size_t size)
{
    struct page *tpage = page_next(page, size);
    /* We must allocate a new page */
    if (tpage->free_size < size)
    {
        struct page *npage = create_page(size);
        /* TODO */
    }
    else
    {

    }
    return tpage;
}
