#ifndef DESSERT_H
# define DESSERT_H

#define BAKE()   \
    int d_f = 0; \
    int d_s = 0; \

#define DESSERT(A)                                          \
    if (!(A))                                               \
    {                                                       \
        printf("[KO] - %s - %s:%d", #A, __FILE__, __LINE__);\
        d_f++;                                              \
    }                                                       \
    else                                                    \
    {                                                       \
        printf("[OK] - %s - %s:%d", #A, __FILE__, __LINE__);\
        d_s++;                                              \
    }                                                       \
    printf(" - test %d\n", d_f + d_s);                      \

#define SERVE()                                         \
    printf("Tests %d/%d succeeded.\n", d_s, d_f + d_s); \

#endif /* DESSERT_H */
