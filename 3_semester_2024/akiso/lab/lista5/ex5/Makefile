all: boot

boot: boot.asm
	nasm -f bin boot.asm -o boot

qemu: boot
	qemu-system-i386 -drive "file=boot,format=raw"

clean:
	rm -f boot