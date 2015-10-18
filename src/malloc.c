#define _GNU_SOURCE
#include "malloc.h"
#include "page.h"
#include "blk.h"
#include "help.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>

/* FIXME Add -Werror flag */

static struct page *get_page(struct page *page, int set)
{
    static struct page *gpage = NULL;
    if (set)
        gpage = page;
    return gpage;
}

static void update_gpage(struct page *page)
{
    while (page->prev)
        page = page->prev;
    get_page(page, 1);
}

void *malloc(size_t size)
{
    size = word_align(size);
    if (size == 0)
        return NULL;
    struct page *page = get_page(NULL, 0);
    struct blk *blk = NULL;
    if (!page)
        page = get_page(create_page(size), 1);
    blk = add_blk(page, size);
    update_gpage(page);
    if (blk)
    {
        return blk + 1;
    }
    else
        return NULL;
}

void *calloc(size_t eltn, size_t elts)
{
    void *ptr = malloc(eltn * elts);
    memset(ptr, 0, eltn * elts);
    return ptr;
}

static void *extend(struct page *page, struct blk *blk, size_t size)
{
    size_t dif = size - blk->size;
    struct blk *fblk = blk->next;
    size_t fsize = fblk->size - dif;
    struct blk *next = fblk->next;

    blk->next = (void *) ((uintptr_t)fblk + dif);
    blk->size = size;
    blk->next->alc = 0;
    blk->next->size = fsize;
    blk->next->next = next;
    blk->next->prev = blk;
    fblk = blk->next;
    if (page)
        update_page(page, page);
    return blk + 1;
}

void *move(struct page *page, void *ptr, struct blk *blk, size_t size)
{
    void *nptr = malloc(size);
    size_t ssize = (blk->size < size) ? blk->size : size;
    nptr = memcpy(nptr, ptr, ssize);
    free_blkp(page, blk + 1);
    return nptr;
}

void *realloc(void *ptr, size_t size)
{
    size = word_align(size);
    if (!ptr)
        return malloc(size);
    if (!size)
        free(ptr);
    struct page *page = get_page(NULL, 0);
    if (!page)
        page = get_page(create_page(size), 1);
    struct blk *blk = (void *)((uintptr_t) ptr - sizeof (struct blk));
    void *nptr = ptr;
    if (blk->size < size)
    {
        if (blk->next && !blk->next->alc && blk->next->size + blk->size > size)
        {
            nptr = extend(page, blk, size);
        }
        else
        {
            nptr = move(page, ptr, blk, size);
        }
    }
    page = get_page(page, 1);
    return nptr;
}

void free(void *ptr)
{
    if (!ptr)
        return;
    struct page *page = get_page(NULL, 0);
    if (!page)
        return NULL;
    page = free_blkp(page, ptr);
    get_page(page, 1);
}
