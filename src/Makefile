OBJS=malloc.c

all: libmalloc.so

libmalloc.so: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o ../$@

check: ../tests/main.o
	$(CC) $(CFLAGS) ../tests/main.o -o main
	./main

include ../common.mk
