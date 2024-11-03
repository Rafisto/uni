CC = gcc
CFLAGS = -Iutil -Wall -pedantic
SRC = rdr.c
OBJ = $(SRC:.c=.o)
TARGET = rdr

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean