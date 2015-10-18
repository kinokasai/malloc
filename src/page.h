#ifndef PAGE_H
# define PAGE_H
# include <stddef.h>
# include "blk.h"

struct page
{
    struct page *next;
    struct page *prev;
    size_t size;
    size_t free_size;
    struct blk *fblk;
};

struct page *create_page(size_t size);
struct page *page_next(struct page *page, size_t size);
struct blk *add_blk(struct page *page, size_t size);
struct page *free_blkp(struct page *page, void *p);
void update_page(struct page *page, struct page *tpage);

#endif /* PAGE_H */
