all: main

main: main.o match.o
	clang -o main main.o match.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

match.o: match.c
	clang -Wextra --pedantic -std=c11 -c match.c

clean:
	rm -f main *.o *~
