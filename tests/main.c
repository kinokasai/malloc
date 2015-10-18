#include <stdlib.h>
#include <signal.h>
#include <stdint.h>

int main(void)
{
    int *lol = malloc(sizeof (int));
    *lol = 3;
    lol = realloc(lol, 16);
}
