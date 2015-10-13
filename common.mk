CC=gcc
CFLAGS=-pedantic -Wall -Wextra -g -std=c99
LDFLAGS=-shared -fPIC

mostlyclean:
	$(RM) $(OBJS) gitcp

clean: mostlyclean
	$(RM) ../gitcp
