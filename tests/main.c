#include <stdio.h>
#include "../src/debug.h"
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    int *lol = malloc(sizeof (int));
    int *erm = malloc(sizeof (int));
    unsigned int uint = -1;
    *lol = 3;
    *erm = 4;
    void *ptr = malloc(9);
    ptr = malloc(17);
    info("Trying to malloc 4096 bytes");
    ptr = malloc(4096);
    printf("lol: %d\n", *lol);
    printf("erm: %d\n", *erm);
    ptr = malloc(6000);
    int *iptr = (void *)((uintptr_t) ptr + 5034);
    *iptr = 3;
    printf("%d\n", *iptr);
    ptr = malloc(6000);
    iptr = (void *)((uintptr_t) ptr + 5034);
    *iptr = 3;
    printf("%d\n", *iptr);
    ptr = malloc(6000);
    iptr = (void *)((uintptr_t) ptr + 5034);
    *iptr = 3;
    printf("%d\n", *iptr);
    ptr = malloc(6000);
    iptr = (void *)((uintptr_t) ptr + 5034);
    *iptr = 3;
    printf("%d\n", *iptr);
    ptr = malloc(6000);
    iptr = (void *)((uintptr_t) ptr + 5034);
    *iptr = 3;
    printf("%d\n", *iptr);
    iptr = malloc(uint);
    return 0;
}
