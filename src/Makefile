OBJS=malloc.o blk.o

all: libmalloc.so

libmalloc.so: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o ../$@

check: libmalloc.so ../tests/main.o
	$(CC) $(CFLAGS) -L.. -lmalloc ../tests/main.o -o ../main
	LD_LIBRARY_PATH=.. ../main

include ../common.mk
