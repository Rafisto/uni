GNATMAKE=gnatmake
EXECUTABLE=bakery
SRC=bakery.adb

all: build

build:
	$(GNATMAKE) $(SRC) -o $(EXECUTABLE)
	rm -f *.ali *.o

run: build
	./$(EXECUTABLE) > out

analyze: run 
	./display-travel-2.bash out

clean:
	rm -f $(EXECUTABLE) *.ali *.o
	rm out