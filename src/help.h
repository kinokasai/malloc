#ifndef HELP_H
# define HELP_H
# include <stddef.h>
# include "blk.h"
# include "page.h"

unsigned long page_align(size_t size);
size_t word_align(size_t size);
void print_mem(struct page *page);
void print_blk(struct blk *blk);

#endif /* HELP_H */
