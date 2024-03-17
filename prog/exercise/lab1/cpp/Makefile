all: test main.o primes.o
	clang++ -Weverything -std=c++11 -I ./ main.o primes.o -o primes -L primes_library/ -lprimes

main.o: main.cpp
	clang++ -Weverything -Wno-c++98-compat -std=c++11 -I ./ -c -Wall main.cpp -o main.o

primes.o: primes.cpp
	clang++ -Weverything -std=c++11 -I ./ -c -Wall primes.cpp -o primes.o

test: tests
	./tests

tests: tests.cpp primes.o
	clang++ -Weverything -std=c++11 -I ./ primes.o -o tests tests.cpp -L primes_library/ -lprimes

clean:
	rm -rf main.o primes.o ./primes tests
