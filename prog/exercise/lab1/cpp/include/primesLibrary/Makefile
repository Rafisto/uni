all: test libprimes.a

test: tests
	./tests

tests: sieve.o tests.o
	clang++ -o tests sieve.o tests.o

libprimes.a: sieve.o
	ar rcs libprimes.a sieve.o

sieve.o: sieve.cpp primes_library.h
	clang++ -c -o sieve.o sieve.cpp

tests.o: tests.cpp primes_library.h
	clang++ -c -o tests.o tests.cpp

clean:
	rm -rf *.o *.so *.a tests