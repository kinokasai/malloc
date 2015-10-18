#include <stdio.h>
#include "../src/debug.h"
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

int main(void)
{
    void *ptr;
    int *lol;
    int i;
    /* Several pages test */
    ptr = malloc(3000);
    ptr = malloc(2000);
    ptr = malloc(64);
    lol = malloc(8);
    free(lol);
   /* ptr = malloc(5000);
    free(ptr);
    ptr = malloc(64);
    i = 0;
    while (i < 1)
    {
        ptr = malloc(64);
        i++;
    }

    // Speed test
    malloc(5000);
    i = 0;
    while (i < 1000000)
    {
        i++;
        if (i%10 == 0)
            free(ptr);
        if (i == 703000)
            raise(SIGTRAP);
        info("malloc n°%d", i);
        ptr = malloc(64);
    }
    free(ptr);

    // Calloc test */
    /*
    int *array = calloc(100, sizeof (int));
    for (int i = 0; i < 100; i++)
        printf("[%d]: %d\n", i, array[i]);
        
    
    //free(erm);

    // Realloc tests 
    lol = malloc(sizeof (int));
    *lol = 3;
    ptr = malloc(400);
    int *erm = malloc(sizeof (int));
    free(ptr);
    lol = realloc(lol, sizeof (int) + 10);
    printf("lol: %d\n", *lol);*/
    return 0;
}
