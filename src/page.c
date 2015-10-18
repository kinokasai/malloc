#define _GNU_SOURCE
#include "page.h"
#include "debug.h"
#include "help.h"
#include "blk.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

size_t get_free_size(struct page *page)
{
    struct blk *blk = page->fblk;
    size_t max = 0;
    while (blk)
    {
        if (!blk->alc && blk->size > max)
            max = blk->size;
        blk = blk->next;
    }
    return max;
}

static struct page *free_page(struct page *page, struct page *opage)
{
    //info("Free'ing page at -> %p", opage);
    if (!opage)
    {
        //warn("OPAGE SHOULDN'T BE NULL");
        return NULL;
    }
    if (opage->prev)
        opage->prev->next = opage->next;
    else
    {
        if (opage->next)
            page = opage->next;
        else
            page = NULL;
    }
    //info("munmap'ing at page -> %p", opage);
    munmap(opage, opage->size);
    return page;
}

static struct page *find_page(struct page *page, void *p)
{
    void *page_end = (void *)((uintptr_t) page + page->size);
    while (page && !(page_end >= p && (void *) page <= p))
    {
        page = page->next;
        if (page)
            page_end = (void *)((uintptr_t) page + page->size);
    }
    return page;
}

void update_page(struct page *page, struct page *tpage)
{
    page->free_size = get_free_size(page);
    size_t nfsize = tpage->free_size + sizeof (struct page);
    if (tpage->size == nfsize)
        page = free_page(page, tpage);
}

/* Checks for the next page capable of containing size */
/* Size may need to be aligned */
struct page *page_next(struct page *page, size_t size)
{
    if (!page)
    {
        //info("This shouldn't happen, I can't find any page");
        return NULL;
    }
    while (page->next)
    {
        if (page->free_size > size)
            return page;
        page = page->next;
    }
    return page;
}

struct page *create_page(size_t size)
{
    //info("Trying to mmap page of %zu bytes", size);
    unsigned long page_size = page_align(size);
    void *mptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (mptr == MAP_FAILED)
    {
        //info("MAP_FAILED!");
        errno = ENOMEM;
        return NULL;
    }
    else
    {
        //info("Mapping %lu bytes of memory", page_size);
        //info("Memory mapped at %p", mptr);
    }
    struct page (*page) = mptr;
    page->next = NULL;
    page->fblk = NULL;
    page->size = page_size;
    page->free_size = page_size - sizeof (struct page) - sizeof (struct blk);
    void *ptr = (void *) ((uintptr_t) page + sizeof (struct page));
    page->fblk = create_blk(ptr, page->free_size);
    //info("Returning page at %p of size %zu", page, page->size);
    return page;
}

/* This should take the first page of the list */
struct blk *add_blk(struct page *page, size_t size)
{
    size = size + sizeof (struct blk);
    struct page *tpage = page_next(page, size);
    //info("Trying to add a blk of size %zu to page of size %zu", size,
    //        tpage->free_size);
    if (tpage->free_size <= size)
    {
        //info("Creating new page...");
        struct page *npage = create_page(size + sizeof (struct blk) * 2
                + sizeof (struct page));
        if (!npage)
            return NULL;
        /* We need to add in head */
        npage->next = page;
        page->prev = npage;
        tpage = npage;
    }
    struct blk *tblk = next_blk(tpage->fblk, size);
    tblk = split_blk(tblk, size);
    tblk->alc = 1;
    if (size > tpage->free_size)
    {
        //warn("UNDERFLOW");
        raise(SIGINT);
    }
    //info("tblk -> %p", tblk);
    tpage->free_size = get_free_size(tpage);
    return tblk;
}

static struct blk *find_blk(struct page *page, void *p)
{
    //info("Searching for block at data -> %p", p);
    //void *page_end = (uintptr_t) page + page->size;
    page = find_page(page, p);
    if (!page)
    {
        //info("Page not found");
        return NULL;
    }
    struct blk *blk = page->fblk;
    while (blk && blk + 1 != p)
        blk = blk->next;
    if (!blk || blk + 1 != p)
    {
        //info("Block not found\n");
        return NULL;
    }
    else
        //info("Block found at %p", blk);
    return (blk + 1 == p) ? blk : NULL;
}

struct page *free_blkp(struct page *page, void *p)
{
    struct blk *blk = find_blk(page, p);
    struct page *tpage = find_page(page, p);
    if (!blk)
        return NULL;

    size_t bsize = free_blk(blk);
    if (tpage->free_size < bsize)
        tpage->free_size = bsize;
    size_t nfsize = tpage->free_size + sizeof (struct page);
    if (tpage->size == nfsize)
        page = free_page(page, tpage);
    return page;
}
