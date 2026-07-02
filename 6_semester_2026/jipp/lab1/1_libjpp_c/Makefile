CC = clang
CFLAGS = -Wall -Wextra -std=c23 -O2 -fPIC

LIB_STATIC = libjpp.a
LIB_DYNAMIC = libjpp.so

SRCS = libjpp.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(LIB_STATIC) $(LIB_DYNAMIC)

$(LIB_STATIC): $(OBJS)
	ar rcs $@ $^

$(LIB_DYNAMIC): $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c libjpp.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB_STATIC) $(LIB_DYNAMIC)
