CXX := clang
CXX_OPT := -O3 -std=c17
CXX_WARN := -Wall -Wextra -Wpedantic \
	-Wno-strict-prototypes -Wno-implicit-function-declaration \
	-Wno-unneeded-internal-declaration -Wno-unused-function \
	-Wno-misleading-indentation
LEX = flex
LEX_FLAGS = -i -I 
CXX_FLAGS = $(CXX_OPT) $(CXX_WARN)

.PHONY:all
all:
	$(MAKE) app --no-print-directory

# (name).lex
# flex -I -i -o (name).yy.c (name).lex
# cxx (flags) (name).yy.c -I./ -o a.out

.PHONY:app
app: $(patsubst %.lex,%.yy.c,$(wildcard *.lex))
	$(CXX) $(CXX_FLAGS) $^ -I./ -o a.out

%.yy.c: %.lex
	$(LEX) $(LEX_FLAGS) -o $@ $<

.PHONY:test
test: app
	diff <(cat ./tests/test.cpp | ./a.out) <(cat ./tests/test.res.cpp) || echo ""
	diff <(cat ./tests/test.cpp | ./a.out --keep-doxygen) <(cat ./tests/test.res.doxygen.cpp) || echo ""

.PHONY:clean
clean:
	rm -f a.out *.yy.c