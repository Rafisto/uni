CC=clang++
CFLAGS=-std=c++23 -Wall -Werror -O2

SRC=main.cpp
OUT=dual.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUT)