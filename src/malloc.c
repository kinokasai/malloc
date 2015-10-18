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
#include <string.h>

/* FIXME Add -Werror flag */

static struct page *get_page(struct page *page, int set)
{
    static struct page *gpage = NULL;
    if (set)
        gpage = page;
    return gpage;
}

void *malloc(size_t size)
{
    info("malloc'ing %zu bytes", size);
    size = word_align(size);
    //info("(%zu bytes word-aligned)", size);
    if (size == 0)
        return NULL;
    struct page *page = get_page(NULL, 0);
    struct blk *blk = NULL;
    if (!page)
        page = get_page(create_page(size), 1);
    blk = add_blk(page, size);
    //print_mem(page);
    if (blk)
    {
        //info("returning %p", blk->data);
        return blk->data;
    }
    else
        return NULL;
}

void *calloc(size_t eltn, size_t elts)
{
    info("Calloc'ing %zu elts of %zu bytes", eltn, elts);
    /* FIXME Check for overflow */
    void *ptr = malloc(eltn * elts);
    memset(ptr, 0, eltn * elts);
    //info("Returning -> %p", ptr);
    return ptr;
}

static void *extend(struct page *page, struct blk *blk, size_t size)
{
    /* This should always be positive */
    size_t dif = size - blk->size;
    struct blk *fblk = blk->next;
    size_t fsize = fblk->size - dif;
    struct blk *next = fblk->next;
    void *data = (void *) ((uintptr_t)fblk->data + dif);

    blk->next = (void *) ((uintptr_t)fblk + dif);
    blk->size = size;
    blk->next->alc = 0;
    blk->next->size = fsize;
    blk->next->next = next;
    blk->next->prev = blk;
    blk->next->data = data;
    fblk = blk->next;
    update_page(page, fblk, fblk->size);
    //info("now blk->size %zu", blk->size);
    return blk->data;
}

void *move(struct page *page, void *ptr, struct blk *blk, size_t size)
{
    //info("We can't extend");
    void *nptr = malloc(size);
    size_t ssize = (blk->size < size) ? blk->size : size;
    //info("Copying %p -> %p for %zu bytes", ptr, nptr, ssize);
    nptr = memcpy(nptr, ptr, ssize);
    free_blkp(page, blk->data);
    //print_mem(page);
    //info("returning -> %p", nptr);
    return nptr;
}

void *realloc(void *ptr, size_t size)
{
    info("realloc'ing %p to size %zu", ptr, size);
    size = word_align(size);
    //info("(%zu bytes word-aligned)", size);
    if (!ptr)
        return malloc(size);
    if (!size)
        free(ptr);
    struct page *page = get_page(NULL, 0);
    struct blk *blk = (void *)((uintptr_t) ptr - sizeof (struct blk));
    //info("Which is");
    //print_blk(blk);
    void *nptr = ptr;
    /* if size < */

    if (blk->size < size)
    {
        //info("We want it bigger");
        if (blk->next && !blk->next->alc && blk->next->size + blk->size > size)
        {
            //info("We can extend");
            nptr = extend(page, blk, size);
        }
        else
        {
            nptr = move(page, ptr, blk, size);
        }
    }
    //print_mem(page);
    return nptr;
}

void free(void *ptr)
{
    info("Free'ing %p", ptr);
    if (!ptr)
    {
        //info("lol it's null");
        return;
    }
    struct page *page = get_page(NULL, 0);
    if (!page)
        return NULL;
    page = free_blkp(page, ptr);
    //print_mem(page);
    get_page(page, 1);
}
