CC      = gnatmake
CFLAGS  = -O2
AFLAGS  = -cargs $(CFLAGS)

TEST_NAME = main

SRC = main.adb

.PHONY: all clean

all: $(TEST_NAME)

$(TEST_NAME): $(SRC)
	$(CC) $(SRC) -o $(TEST_NAME) $(AFLAGS)

clean:
	rm -f *.o *.ali $(TEST_NAME)