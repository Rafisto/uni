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

msg: .ascii "[rw-bootloader] version 0.01\r\nHi Bois!\r\n"

# .fill creates a block of memory filled with a specific value
# .fill <size>, <repetitions>, <value>
.fill 510-(.-_start), 1, 0 # fill the rest of the 510 bytes with zeros

# add the magic number at the end of the bootloader
.word 0xaa55 # little endian
