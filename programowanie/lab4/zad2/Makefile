all: main

main: main.o coder.o decoder.o
	clang -lm -o main main.o coder.o decoder.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

coder.o: coder.c
	clang -Wextra --pedantic -std=c11 -c coder.c

decoder.o: decoder.c
	clang -Wextra --pedantic -std=c11 -c decoder.c

clean:
	rm -f main *.o *~