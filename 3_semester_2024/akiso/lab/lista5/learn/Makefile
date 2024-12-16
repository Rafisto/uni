# Make all *.asm files into binaries

CC = nasm
CFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386
SRC = $(wildcard *.asm)
OBJ = $(SRC:.asm=.o)
BIN = $(SRC:.asm=)

.PHONY: all clean

all: $(BIN)

%.o: %.asm
	$(CC) $(CFLAGS) -o $@ $<

%: %.o
	$(LD) $(LDFLAGS) -o $@ $<
	rm -f $<

clean:
	rm -f $(OBJ) $(BIN)