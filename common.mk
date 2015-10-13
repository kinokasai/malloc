CC=gcc
CFLAGS=-pedantic -Wall -Wextra -g -std=c99 -fPIC
LDFLAGS=-shared

mostlyclean:
	$(RM) $(OBJS) ../libmalloc.so ../tests/main.o

clean: mostlyclean
	$(RM) ../libmalloc.so main.o
