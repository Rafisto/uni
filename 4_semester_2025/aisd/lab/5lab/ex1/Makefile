CPP_FILES := $(wildcard *.cpp)
OUT_FILES := $(CPP_FILES:.cpp=.out)

CXX := clang++
CXXFLAGS := -O3 -Wall -Werror -Wconversion -Wextra -Wsign-conversion -Wpedantic -Wvla
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --error-exitcode=1

.PHONY: all test memcheck clean

all: $(OUT_FILES) test

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: $(OUT_FILES)
	@for file in $(OUT_FILES); do \
		./$$file 8; \
	done

memcheck: $(OUT_FILES)
	@for file in $(OUT_FILES); do \
		valgrind $(VALGRIND_FLAGS) ./$$file 8; \
	done

clean:
	rm -f $(OUT_FILES) *.o