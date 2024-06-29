all: main

main: main.o phi.o gcd.o
	clang -lm -o main main.o phi.o gcd.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

phi.o: phi.c
	clang -Wextra --pedantic -std=c11 -c phi.c

gcd.o: gcd.c
	clang -Wextra --pedantic -std=c11 -c gcd.c

clean:
	rm -f main *.o *~