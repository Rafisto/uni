.PHONY: all
all:
	as -o boot.o boot.s
	objcopy --remove-section=.note.gnu.property boot.o
	ld -o boot.bin --oformat binary boot.o -Ttext 0x7c00

.PHONY: clean
clean:
	rm -f boot.o boot.bin