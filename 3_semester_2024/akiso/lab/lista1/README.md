# Lista 1

- [Lista 1](#lista-1)
- [Słownik](#słownik)
  - [Zadanie 1](#zadanie-1)
    - [VirtualBox](#virtualbox)
    - [QEMU](#qemu)
    - [`libvirt`](#libvirt)
  - [Zadanie 2](#zadanie-2)
    - [BIOS](#bios)
    - [UEFI](#uefi)
    - [GPT](#gpt)
    - [MBR](#mbr)
    - [System Plików](#system-plików)
    - [FreeBSD](#freebsd)
    - [`jails`](#jails)
    - [`bhyve`](#bhyve)
  - [Terminy od WW](#terminy-od-ww)
    - [S.M.A.R.T.](#smart)
    - [POST](#post)
    - [Bootloader](#bootloader)
    - [NCQ](#ncq)
    - [LBA](#lba)
    - [SCSI](#scsi)
    - [DMA](#dma)
    - [INT / IRQ](#int--irq)
    - [EPROM / EEPROM](#eprom--eeprom)
    - [Flash](#flash)
- [Zadania](#zadania)
  - [Zadanie 1, 2, 3](#zadanie-1-2-3)
  - [Zadanie 4](#zadanie-4)
  - [Zadanie 5](#zadanie-5)

# Słownik

## Zadanie 1

### VirtualBox

Made by Oracle. It is a virtualization software that allows you to run multiple operating systems on a single machine.

### QEMU

It is a generic and open source machine emulator and virtualizer.

### `libvirt`

It is a toolkit to manage virtualization platforms. It is a C toolkit that offers a high-level API for managing virtualization.

## Zadanie 2

### BIOS

**Basic Input/Output System** is a firmware that is used to perform hardware initialization during the booting process. It is the first software that runs when you start your computer.

### UEFI

**Unified Extensible Firmware Interface** is an interface between the operating system and the platform firmware. It is a replacement for the BIOS.

### GPT

**General Partition Table** is a standard for the layout of the partition table on a physical hard disk. It is a part of the UEFI standard.

### MBR

**Master Boot Record** is a special type of boot sector at the very beginning of partitioned computer mass storage devices like fixed disks or removable drives.

Very difficult to repartiotion, replaced by GPT.

### System Plików

**Filesystem** is a method of organizing data on a storage device. It specifies how data is stored, retrieved, and updated.

Linux mainly uses:
- **EXT4** - Extended File System 4 - is the default file system for many Linux distributions.
- **ZFS** - Zettabyte File System - is a combined file system and logical volume manager designed by Sun Microsystems. Nobody understands it, pure magic.

### FreeBSD

FreeBSD is an open-source operating system. It is a Unix-like operating system based on the Berkeley Software Distribution (BSD).

MacOS is a close relative to FreeBSD.

### `jails`

FreeBSD jails are a lightweight virtualization technology that allows you to run multiple instances of FreeBSD on a single host.

### `bhyve`

It is a hypervisor that runs on FreeBSD. It is a type-2 hypervisor that runs on top of an existing operating system.

## Terminy od WW

### S.M.A.R.T.

**Self-Monitoring, Analysis, and Reporting Technology** is a monitoring system included in computer hard disk drives (HDDs), solid-state drives (SSDs), and eMMC drives.

### POST

**Power-On Self-Test** is a diagnostic testing sequence run by the computer's BIOS as the computer boots.

### Bootloader

A bootloader is a small program that loads the operating system into the computer's memory. It is the first program that runs when you start your computer.

<section>
<details>
An example bootloader:
</details>

```s
# r-os
# rafal wlodarczyk 2024
# qemu-system-x86_64 boot.bin
# bootloader must be a 512 byte binary file that contains 0x55AA at the end (a magic number)

# at the beginning the CPU runs in the 16 bit real mode
.code16 # using 16-bit mode for x86
.global _start # _start is the entry point of the bootloader

_start: 
  mov $msg, %si # loads the address of msg into si 
  mov $0xe, %ah # loads 0xe (function number for int 0x10) into ah 

print_char: 
  lodsb # loads the byte from the address in si into al and increments si 
  cmp $0, %al # compares content in AL with zero 
  je done # if al == 0, go to "done" 
  int $0x10 # prints the character in al to screen 
  jmp print_char # repeat with next byte 

done: 
  hlt # stop execution 

msg: .ascii "[nos] version 0.01\r\Not an operating system\r\n"

# .fill creates a block of memory filled with a specific value
# .fill <size>, <repetitions>, <value>
.fill 510-(.-_start), 1, 0 # fill the rest of the 510 bytes with zeros

# add the magic number at the end of the bootloader
.word 0xaa55 # little endian
```

</section>

### NCQ

**Native Command Queuing** is an extension of the Serial ATA protocol that allows hard disk drives to internally optimize the order in which read and write commands are executed

### LBA

**Logical Block Addressing** is a common scheme used for specifying the location of blocks of data stored on computer storage devices, generally secondary storage systems such as hard disks.

### SCSI

**Small Computer System Interface** is a set of standards for physically connecting and transferring data between computers and peripheral devices.

### DMA

**Direct Memory Access** is a feature of computer systems that allows certain hardware subsystems to access main system memory independently of the central processing unit (CPU).

### INT / IRQ

**Interrupt Request** is a signal sent to the computer processor to stop the current process and perform a specific task.

### EPROM / EEPROM

**Erasable Programmable Read-Only Memory** is a type of non-volatile memory that can be erased and reprogrammed.
**Electrically Erasable Programmable Read-Only Memory** is a type of non-volatile memory that can be erased and reprogrammed using an electric field.

### Flash

**Flash memory** is a type of non-volatile storage that can be electrically erased and reprogrammed. It is used in memory cards, USB flash drives, and solid-state drives.

# Zadania

## Zadanie 1, 2, 3

<section>
<details>
Installation backlog (UEFI)
</details>

1. Ensure `efivars` are loaded `ls /sys/firmware/efi/efivars`
2. `fdisk` setup should return the following partition table:

```bash
Device            Start        End   Sectors   Size Type
/dev/nvme0n1p1     2048    2099199   2097152     1G EFI System
/dev/nvme0n1p2  2099200   10487807   8388608     4G Linux swap
/dev/nvme0n1p3 10487808 1000214527 989726720 471.9G Linux filesystem
```

3. Run `mkfs` on efi and filesystem

```bash
mkfs.fat -F 32 /dev/nvme0n1p1
mkfs.ext4 /dev/nvme0n1p3
```

4. Run `mkswap`

```bash
mkswap /dev/nvme0n1p2
swapon /dev/nvme0n1p2
```

5. Mount `fs`:

```bash
mount /dev/nvme0n1p3 /mnt
mount --mkdir /dev/nvme0n1p1 /mnt/boot
```

6. Pacstrap the base packages

```bash
pacstrap -K /mnt base linux linux-firmware gnome gdm networkmanager
```

7. Gen `fstab` at `rootfs`

```bash
genfstab -U /mnt >> /mnt/etc/fstab
```

8. Chroot `arch`

```bash
arch-chroot /mnt
```

9. Set clock

```bash
ls /usr/share/zoneinfo/
ln -s /usr/share/zoneinfo/Europe/Warsaw /etc/localtime
hwclock --systohc
```

10. Set locale and hostname

```bash
vim /etc/locale.gen (uncomment en_US.UTF-8 UTF-8)
locale-gen
echo LANG=en_US.UTF-8 > /etc/locale.conf
# hostname
echo vmkitty > /etc/hostname
```

11. Create user:

```bash
useradd -m -G wheel --shell /bin/bash yourusername
passwd yourusername
visudo
# ---> Uncomment "%wheel ALL=(ALL) ALL"
```

12. Setup GRUB:

```bash
pacman -S grub efibootmgr
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB
```

</section>

## Zadanie 4

Setup backlog

```bash
git clone https://github.com/mit-pdos/xv6-public.git xv6
cd xv6
wget https://cs.pwr.edu.pl/zawada/so/xv6.patch
patch -p1 -i xv6.patch

make qemu-nox
make qemu-nox-gdb

echo "set auto-load safe-path /" >>~/.gdbinit

gdb ./kernel
(gdb) break *0x7c00 # This breakpoint represents the boot section.
(gdb) c
```

## Zadanie 5

Install FreeBSD.
