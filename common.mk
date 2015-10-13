CC=gcc
CFLAGS=-pedantic -Wall -Wextra -g -std=c99 -fPIC
LDFLAGS=-shared

mostlyclean:
	$(RM) $(OBJS) ../libmalloc.so

clean: mostlyclean
	$(RM) ../libmalloc.so
