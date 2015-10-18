#include <stdio.h>
#include "../src/debug.h"
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    void *ptr;
    int *lol;
    /* Several pages test */
    /*lol = malloc(sizeof (int));
    malloc(5000);
    ptr = malloc(64);*/

    /* Speed test */
   /* malloc(5000);
    int i = 0;
    while (i < 100000)
    {
        i++;
        info("malloc n°%d", i);
        if (i%10 == 0)
            free(ptr);
        ptr = malloc(64);
    }
    free(ptr);*/

    /* Calloc test */
    /*
    int *array = calloc(100, sizeof (int));
    for (int i = 0; i < 100; i++)
        printf("[%d]: %d\n", i, array[i]);
        */
    
    //free(erm);

    /* Realloc tests */
    printf("\n");
    info("Now reallocating \n");
    
    lol = malloc(sizeof (int));
    *lol = 3;
    ptr = malloc(400);
    int *erm = malloc(sizeof (int));
    free(ptr);
    lol = realloc(lol, sizeof (int) + 10);
    printf("lol: %d\n", *lol);
    return 0;
}
