#include "blk.h"
#include <stdlib.h>
#include <stdint.h>

struct blk *find_next(struct blk *blk, size_t size)
{
    while (blk->next && !(blk->state == 0 && size > blk->size))
    {
        blk = blk->next;
    }
    return blk;
}

/* size should be size_t aligned */
struct blk *alloc(struct blk *blk, size_t size)
{
    struct blk *tblk = find_next(blk, size);

    void *ptr = tblk;
    ptr = (void *) ((uintptr_t) ptr + sizeof (struct blk) + tblk->size);
    struct blk *nblk = ptr;
    nblk->state = 1;
    nblk->size = size;
    nblk->next = NULL;
    nblk->data = nblk + sizeof (struct blk);
    tblk->next = nblk;
    return nblk;
}
