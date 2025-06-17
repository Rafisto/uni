GNATMAKE=gnatmake
EXECUTABLE=travelers
SRC=travelers.adb

all: build

build:
	$(GNATMAKE) $(SRC) -o $(EXECUTABLE)
	rm -f *.ali *.o

run: build
	./$(EXECUTABLE) > out

analyze: run 
	../display-travel.bash out

clean:
	rm -f $(EXECUTABLE) *.ali *.o