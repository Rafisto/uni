EXECUTABLE=szymanski

all: build

build:
	go build -o $(EXECUTABLE)

run: build
	./$(EXECUTABLE) > out

analyze: run
	../ex1/display-travel-2.bash out

clean:
	rm -f $(EXECUTABLE)
	rm out
