#include <stdio.h>

int main(void)
{
    int *lol = malloc(sizeof (int));
    *lol = 3;
    printf("lol: %d", *lol);
    return 0;
}
