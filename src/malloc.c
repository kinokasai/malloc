#define _GNU_SOURCE
#include "malloc.h"
#include <sys/mman.h>

void *malloc(size_t size)
{
    void *mptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);
    return mptr;
}

void free(void *ptr)
{

}
