all: boot

boot: boot.asm
	nasm -f bin boot.asm -o boot

qemu: boot
	qemu-system-i386 -drive "file=boot,format=raw"

clean:
	rm -f boot

# sudo parted /dev/sdX mklabel msdos
# sudo parted /dev/sdX mkpart primary fat32 1MiB 100%
# sudo mkfs.vfat /dev/sdX1

# sudo dd if=boot of=/dev/sdX bs=512 count=1 conv=sync