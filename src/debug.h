#ifndef DEBUG_H
# define DEBUG_H
# include <stdio.h>

#define info(M, ...)                                    \
    fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, \
            __LINE__, ##__VA_ARGS__)

#endif /* DEBUG_H */
