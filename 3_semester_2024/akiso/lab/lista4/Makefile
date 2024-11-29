CC = gcc

# ignore ex3 folder
SRC = $(shell find . -name '*.c' -not -path "./ex3/*") 
OUT = $(SRC:.c=.out)

all: $(OUT)

%.out: %.c
	$(CC) $< -o $@

clean:
	rm -f $(OUT)