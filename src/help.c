#include "help.h"
#include <unistd.h>
#include <stdint.h>

unsigned long page_align(size_t size)
{
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long tmp = page_size;
    tmp += size / tmp * page_size;
    return tmp;
}

size_t word_align(size_t size)
{
    size_t tsize = sizeof (size_t);
    return (size - 1) / tsize * tsize + tsize;
}
