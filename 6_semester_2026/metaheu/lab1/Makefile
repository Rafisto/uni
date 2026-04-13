CC=clang++
CFLAGS=-std=c++23 -O3 -march=native -ftree-vectorize -fopenmp

INPUT=$(wildcard *.cpp)
OUTPUT=$(INPUT:.cpp=.out)

all: $(OUTPUT)

%.out: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OUTPUT)
