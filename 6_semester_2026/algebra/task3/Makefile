CC=clang++
CFLAGS=-std=c++23 -Wall -Werror -O2

SRC=buchberger.cpp
OUT=buchberger.out

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OUT)