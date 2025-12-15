CXX := clang++
CXX_OPT := -O3 -std=c++23
CXX_DBG := # -ggdb3
CXX_WARN := -Weverything  -Wno-c++98-compat-pedantic -Wno-shadow-field-in-constructor \
 			-Wno-weak-vtables -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors \
			-Wno-unsupported-cb -Wno-unsafe-buffer-usage -Wno-newline-eof -Wall -Werror -Wextra \
			-pedantic -Wconversion -Wsign-conversion
# 			-D_LIBCPP_HARDENING_MODE=D_LIBCPP_HARDENING_MODE_EXTENSIVE
# 			-D_GLIBCXX_ASSERTIONS

CXX_FLAGS = $(CXX_OPT) $(CXX_DBG) $(CXX_WARN)
LDFLAGS  := -licui18n -licuuc -licudata

.PHONY:all
all:
	$(MAKE) app --no-print-directory
# 	$(MAKE) valgrind --no-print-directory

.PHONY:app
app:
	$(CXX) $(CXX_FLAGS)  ./*.cpp -I./ -o ./a.out $(LDFLAGS)

.PHONY:valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./a.out 


.PHONY:test
test:
	$(CXX) $(CXX_FLAGS)  ./test/*.cpp -I./ -o ./test.out

.PHONY:analyze
analyze: app test
	clang++ --analyze -Xanalyzer -analyzer-output=text -I./  ./*.cpp test/*.cpp
	clang-tidy --quiet -checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cert-*,concurrency-*,misc-*,modernize-*,performance-*,readability-*,-modernize-use-trailing-return-type --warnings-as-errors=* ./*.cpp  -- -I./

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
	$(CXX) $(CXX_FLAGS)  ./test/*.cpp -I./ -o ./test.out
	./test.out

.PHONY:sanitizer_undefined
sanitizer_undefined: CXX_FLAGS += -fsanitize=undefined -ggdb3
sanitizer_undefined:
	$(MAKE) clean --no-print-directory
	$(CXX) $(CXX_FLAGS)  ./test/*.cpp -I./ -o ./test.out
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
	rm -rf a.out
	rm -rf test.out