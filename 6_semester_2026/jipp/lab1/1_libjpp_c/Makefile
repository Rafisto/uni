CC=clang

all: main

main: libjpp.a libjpp.so

libjpp.a: libjpp.c libjpp.h
	$(CC) -c libjpp.c -o libjpp.o
	ar rcs libjpp.a libjpp.o

libjpp.so: libjpp.c libjpp.h
	$(CC) -fPIC -shared libjpp.c -o libjpp.so

clean:
	rm -f libjpp.o libjpp.a libjpp.so