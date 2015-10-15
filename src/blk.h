#ifndef BLK_H
# define BLK_H
# include <stddef.h>

struct blk
{
    int state;
    size_t size;
    struct blk *next;
    void *data;
};

struct blk *find_next(struct blk *blk, size_t size);
struct blk *alloc(struct blk *blk, size_t size);

#endif /* BLK_H */
