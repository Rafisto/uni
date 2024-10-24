These instructions work on Ubuntu 18.04

### Prerequisites

* Install Qemu

You can run this boot into Rust demo under Qemu emulator or on baremetal hardware. 
I suggest to try Qemu first. Install Qemu

```
sudo apt-get install qemu
```

* Install nasm

To build the ASM files you'll need nasm: 

```
sudo apt-get install nasm
```

### Run under QEMU 

```
make qemu
```

If you see complains from the `grub-mkrescue`, install the `xorriso` package
```
grub-mkrescue: warning: Your xorriso doesn't support `--grub2-boot-info'. Some features are disabled. Please use xorriso 1.2.9 or later..                                                 
```

### Debug wigh QEMU and GDB

You will need two shell windows opened in the same folder. In the first shell type: 

```
make qemu
```

In the other shell start gdb like

```
gdb
```


### Boot on baremetal from a USB drive

Copy the ISO disk image to the USB stick (make sure to use correct device for the 
USB drive, otherwise you can overwrite your hard disk). You can use lsblk on Ubuntu
to list block devices

```
lsblk
```

For me it's /dev/sda or /dev/sdb but my laptop runs off an NVMe device, so for you 
/dev/sda may very well be your root device, not a USB!

```
sudo dd if=build/hello.iso of=/dev/<your_usb_drive> bs=1MB
sync
```

### Boot on baremetal from a Linux partition

``` 
sudo cp build/kernel.bin /boot/
```
Add the following entry to the grub menu list. On a Linux machine this can
be done by adding this to the /etc/grub.d/40_custom. You might adjust the
root='hd0,2' to reflect where your Linux root is on disk, e.g., maybe it's on
root='hd0,1'

```
set timeout=30
menuentry "Hello World" {
    insmod ext2
    set root='hd0,1'
    set kernel='/boot/kernel.bin'
    echo "Loading ${kernel}..."
    multiboot2 ${kernel} ${kernel}
    boot
}
```

Update grub

```
  sudo sudo update-grub2
```

Reboot and choose the "Hello World" entry. Make sure that you can see the grub menu
list by editing /etc/default/grub making sure that GRUB_HIDDEN_TIMEOUT_QUIET is
set to "false". 

```
  GRUB_HIDDEN_TIMEOUT_QUIET=false
```

