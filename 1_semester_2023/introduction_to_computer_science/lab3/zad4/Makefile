all: main

main: main.o newagent.o distance.o north.o south.o east.o west.o
	clang -lm -o main main.o newagent.o distance.o north.o south.o east.o west.o

main.o: main.c
	clang -Wextra --pedantic -std=c11 -c main.c

newagent.o: newagent.c
	clang -Wextra --pedantic -std=c11 -c newagent.c

distance.o: distance.c
	clang -Wextra --pedantic -std=c11 -c distance.c

north.o: north.c
	clang -Wextra --pedantic -std=c11 -c north.c

south.o: south.c
	clang -Wextra --pedantic -std=c11 -c south.c

east.o: east.c
	clang -Wextra --pedantic -std=c11 -c east.c

west.o: west.c
	clang -Wextra --pedantic -std=c11 -c west.c

clean:
	rm -f main *.o *~