all: main.o primes.o
	clang++ -Weverything -std=c++11 -I ./include/ ./app/main.o ./app/primes.o -o ./app/primes -L ./include/primes_library/ -lprimes

main.o: ./app/main.cpp
	clang++ -Weverything -Wno-c++98-compat -std=c++11 -I ./include/ -c -Wall ./app/main.cpp -o ./app/main.o

primes.o: ./app/primes.cpp
	clang++ -Weverything -std=c++11 -I ./include/ -c -Wall ./app/primes.cpp -o ./app/primes.o

clean:
	rm -f ./app/*.o ./app/primes