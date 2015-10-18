#ifndef MALLOC_H
# define MALLOC_H
# include <stddef.h>

void *malloc(size_t size);
void *calloc(size_t eltn, size_t elts);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

#endif /* MALLOC_H */
