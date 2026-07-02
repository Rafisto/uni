CC=clang++
CFLAGS=-std=c++23 -Wall -Wextra
COPT=-O2 -march=native -ftree-vectorize -funroll-loops
# CEXTRA=-fsanitize=undefined -fsanitize=address -g
CMULTIPROCESS=-fopenmp 

INPUT=$(wildcard *.cpp)
OUTPUT=$(INPUT:.cpp=.out)

all: $(OUTPUT)

%.out: %.cpp
	$(CC) $(CFLAGS) $(COPT) $(CEXTRA) $(CMULTIPROCESS) -o build_$@ $<

clean:
	rm -rf build_*.out
