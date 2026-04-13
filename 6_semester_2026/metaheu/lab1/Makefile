CC=clang++
CFLAGS=-std=c++23
COPT=-O3 -march=native -ftree-vectorize -funroll-loops -ffast-math
CMULTIPROCESS=-fopenmp 

INPUT=$(wildcard *.cpp)
OUTPUT=$(INPUT:.cpp=.out)

all: $(OUTPUT)

%.out: %.cpp
	$(CC) $(CFLAGS) $(COPT) $(CMULTIPROCESS) -o $@ $<

clean:
	rm -rf $(OUTPUT)
