all: main

main: main.o rozwiazanie.o f.o
	clang -lm -o main main.o rozwiazanie.o f.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

rozwiazanie.o: rozwiazanie.c
	clang -Wextra --pedantic -std=c11 -c rozwiazanie.c

f.o: f.c
	clang -Wextra --pedantic -std=c11 -c f.c

clean:
	rm -f main *.o *~