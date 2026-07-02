CC=clang++
CFLAGS=-Wall -Wextra -std=c++23 -O2

OUTPUT=main

SRCS = main.cpp libjpp.cpp

.PHONY: all clean

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRCS)

clean:
	rm -f $(OBJS) $(OUTPUT)
