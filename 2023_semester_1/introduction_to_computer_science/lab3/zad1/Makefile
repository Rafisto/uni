all: main

main: main.o palindrom.o
	clang -o main main.o palindrom.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

palindrom.o: palindrom.c
	clang -Wextra --pedantic -std=c11 -c palindrom.c

clean:
	rm -f main *.o *~
