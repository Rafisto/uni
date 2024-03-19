# Simple Makefile, do not use this shit :P

CXX := clang++
CXX_OPT := -O3
CXX_DBG := # -ggdb3
CXX_WARN := -Weverything -Wno-c++98-compat-pedantic -Wno-shadow-field-in-constructor \
 			-Wno-weak-vtables -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors \
			-Wno-unsupported-cb -Wno-newline-eof

CXX_FLAGS = $(CXX_OPT) $(CXX_DBG) $(CXX_WARN)

.PHONY:all
all:
	$(MAKE) app --no-print-directory

.PHONY:app
app:
	$(CXX) $(CXX_FLAGS) ./src/*.cpp ./app/*.cpp -I./include -o ./app.out

.PHONY:test
test:
	$(CXX) $(CXX_FLAGS) ./src/*.cpp ./test/*.cpp -I./include -o ./test.out

.PHONY:analyze
analyze: app test
	clang++ --analyze -Xanalyzer -analyzer-output=text -I./include ./src/*.cpp ./app/*.cpp test/*.cpp
	clang-tidy --quiet -checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cert-*,concurrency-*,misc-*,modernize-*,performance-*,readability-*,-modernize-use-trailing-return-type --warnings-as-errors=* ./app/*.cpp ./src/*.cpp -- -I./include

.PHONY:memcheck
memcheck: test
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./test.out

.PHONY:sanitizer
sanitizer:
	$(MAKE) sanitizer_address --no-print-directory
	$(MAKE) sanitizer_undefined --no-print-directory

.PHONY:sanitizer_address
sanitizer_address: CXX_FLAGS += -fsanitize=address -ggdb3
sanitizer_address:
	$(MAKE) clean --no-print-directory
	$(CXX) $(CXX_FLAGS) ./src/*.cpp ./test/*.cpp -I./include -o ./test.out
	./test.out

.PHONY:sanitizer_undefined
sanitizer_undefined: CXX_FLAGS += -fsanitize=undefined -ggdb3
sanitizer_undefined:
	$(MAKE) clean --no-print-directory
	$(CXX) $(CXX_FLAGS) ./src/*.cpp ./test/*.cpp -I./include -o ./test.out
	./test.out


.PHONY:regression
regression:
	$(MAKE) clean --no-print-directory
	$(MAKE) app --no-print-directory
	$(MAKE) test --no-print-directory
	$(MAKE) analyze --no-print-directory
	./test.out
	$(MAKE) sanitizer --no-print-directory
	$(MAKE) memcheck --no-print-directory

.PHONY:clean
clean:
	rm -rf app.out
	rm -rf test.out