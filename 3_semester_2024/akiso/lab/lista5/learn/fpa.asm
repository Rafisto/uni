section .data
    x dd 1.2 ; 4 bytes of floating point data
    y dd 2.4 ; 4 bytes of floating point data

section .text
global _start

_start:
    fld dword [x]
    fld dword [y]
    fadd
    fstp dword [x]

    ; Exit program
    mov eax, 1          ; syscall: exit
    xor ebx, ebx        ; status 0
    int 0x80