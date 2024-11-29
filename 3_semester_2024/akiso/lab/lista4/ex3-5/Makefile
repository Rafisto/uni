CC = gcc
CFLAGS = -Ilib -Wall -pedantic
OUTPUT = lsh

.PHONY:all
all: 
	$(MAKE) app --no-print-directory

.PHONY:app
app:
	$(CXX) $(CXX_FLAGS) ./*.c ./src/*.c -I./lib -o $(OUTPUT)

.PHONY:clean
clean:
	rm -f $(OUTPUT) *.o
