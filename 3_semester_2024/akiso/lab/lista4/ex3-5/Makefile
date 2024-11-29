CC = gcc
CFLAGS = -Ilib -Wall -pedantic
OUTPUT = lsh
TEST_OUTPUT = testlsh

.PHONY:all
all: 
	$(MAKE) app --no-print-directory

.PHONY:app
app:
	$(CXX) $(CXX_FLAGS) ./*.c ./src/*.c -I./lib -o $(OUTPUT)

.PHONY:test
test:
	$(CXX) $(CXX_FLAGS) ./test/*.c ./src/*.c -I./lib -o $(TEST_OUTPUT)

.PHONY:clean
clean:
	rm -f $(OUTPUT) *.o