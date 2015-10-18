CC=gcc
CFLAGS=-pedantic -Wall -Wextra -Werror -g -std=c99 -fPIC
LDFLAGS=-shared

mostlyclean:
	$(RM) $(OBJS) ../libmalloc.so ../main

clean: mostlyclean
	$(RM) ../libmalloc.so ../tests/main.o
