#include <stdio.h>
#include "../src/debug.h"

int main(void)
{
    int *lol = malloc(sizeof (int));
    void *erm = malloc(5123);
    *lol = 3;
    printf("lol: %d", *lol);
    return 0;
}
