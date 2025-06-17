EXECUTABLE=travelers

all: build

build:
	go build -o $(EXECUTABLE)

run: build
	./$(EXECUTABLE) > out

analyze: run
	../display-travel.bash out

clean:
	rm -f $(EXECUTABLE)
