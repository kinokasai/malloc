#ifndef BLK_H
# define BLK_H
# include <stddef.h>

struct blk
{
    int alc;
    size_t size;
    struct blk *next;
    struct blk *prev;
    void *data;
};

struct blk *create_blk(void *p, size_t size);
struct blk *split_blk(struct blk *blk, size_t size);
struct blk *next_blk(struct blk *blk, size_t size);
int free_blk(struct blk *blk);

#endif /* BLK_H */
