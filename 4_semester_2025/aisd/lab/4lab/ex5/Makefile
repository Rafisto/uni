SOURCE := test.cpp
OUTFILE := test.out

CXX := clang++
CXX_OPT := -O3
CXX_WARN := -Wall -Werror -Wconversion -Wextra -Wsign-conversion -Wpedantic -Wvla
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --error-exitcode=1

.PHONY: all test memcheck clean

all: $(OUTFILE)

$(OUTFILE): $(SOURCE)
	g++ $(SOURCE) -o $(OUTFILE) $(CXX_OPT) $(CXX_WARN)

test: $(OUTFILE)
	./$(OUTFILE)

memcheck: $(OUTFILE)
	valgrind $(VALGRIND_FLAGS) ./$(OUTFILE)

clean:
	rm -f $(OUTFILE) *.o