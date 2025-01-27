## Learning about FAT

FAT - File Allocation Table - file system developed in 1977.
- Replaced with NTFS on Windows, can still be used on USB drives.
- Used internally for the EFI system partition.

The file system uses an index table stored on the device to identify chains of data storage areas associated with a file.
- The table is a linked list of entries for each cluster

Limits (FATx means x is the the size of a linked list entry):
- FAT12: 32 MB (256 MB for 64 KB clusters)
- FAT16: 2 GB (4 GB for 64 KB clusters)
- FAT32: 2 TB (16 TB for 4 KB sectors)

### Create FAT file system in Linux.

Install dosfstools package:

```bash
pacman -S dosfstools 
```

Create a FAT file system:

```bash
cd /tmp
dd if=/dev/zero of=fat.img bs=1024 count=1024
mkfs.msdos fat.img
mkdir -p /tmp/fs
mount -t msdos fat.img /tmp/fs -o umask=000,loop
cd /tmp/fs
echo "hello, world" > hello
```

Examine the FAT file system:

```bash
hexdump -C /tmp/fat.img | less
# -C = Cannonical hex+ASCII display
od -Ax -tx1z /tmp/fat.img | less
# -A = output format for file offsets (Ax means hexadecimal)
# -t = output format for data (tx1z means hexadecimal, one byte per line, zero-terminated)
```

Create a few files (one exceeding the single cluster size):

```bash
echo "hello, world" > /tmp/fat.fs/hello
echo "hello, world" > /tmp/fat.fs/hello2
```

### Create a VFAT file system:

Create a VFAT file system:

```bash
mkdir -p /tmp/vfat.fs/
dd if=/dev/zero of=/tmp/vfat.img bs=1024 count=1024
mkfs.vfat /tmp/vfat.img
sudo mount -t vfat /tmp/vfat.img /tmp/vfat.fs/ -o umask=000,loop
echo "hello, world" > /tmp/vfat.fs/hello
```

Examine the VFAT file system:

```bash
hexdump -C /tmp/vfat.img | less
```