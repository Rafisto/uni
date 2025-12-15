CXX := clang++
CXXFLAGS := -Wall -Wextra -std=c++20
CXXOPT := -O3 -march=native -ftree-vectorize -funroll-loops -flto -fno-exceptions
INPUT_DIR := ../../ch9-1.1/inputs
# -fprofile-generate

SRC := run.cpp
OUT := radix_heap

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(CXXOPT) -o $@ $<
# 	LLVM_PROFILE_FILE=profile.profraw ./dijkstra -d $(INPUT_DIR)/Long-C/Long-C.0.0.gr -ss $(INPUT_DIR)/Long-C/Long-C.0.0.ss -oss /dev/null
# 	llvm-profdata merge -output=code.profdata profile.profraw
# 	$(CXX) $(CXXFLAGS) -fprofile-use=code.profdata -o $@.out $<

clean:
	rm -f $(OUT)
# 	rm -f $(OUT).out
# 	rm -f *.profraw
# 	rm -f *.profdata

.PHONY: all clean
