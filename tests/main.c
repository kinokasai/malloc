#include <stdio.h>
#include "../src/debug.h"
#include <stdlib.h>

int main(void)
{
    int *lol = malloc(sizeof (int));
    int *erm = malloc(sizeof (int));
    *lol = 3;
    *erm = 4;
    void *ptr = malloc(9);
    ptr = malloc(17);
    printf("lol: %d\n", *lol);
    printf("erm: %d\n", *erm);
    return 0;
}
