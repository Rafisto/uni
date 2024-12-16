
; nasm -fbin boot.asm
; qemu-system-i386 -drive format=raw,file=boot

bits 16
org 0x7c00

boot:
    mov ax, 0x2401
    int 0x15
    mov ax, 0x13        ; wlaczenie trybu graficznego 320x200
    int 0x10
    cli
    lgdt [gdt_pointer]  ; ustawienie tablicy GDT
    mov eax, cr0        ; wlaczenie trybu chronionego
    or eax,0x1
    mov cr0, eax
    jmp CODE_SEG:boot2
gdt_start:              ; tablica GDT
    dq 0x0
gdt_code:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0
gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
boot2:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebx,0xa0000     ; adres ekranu graficznego
    mov cx,200          ; 200 lini ekranu
.loop2:
    mov dx,320          ; 320 piksli na linie
.loop1:
    mov byte [ebx], cl
    add ebx,1
    dec dx
    jne .loop1
    loop .loop2
halt:
    cli
    hlt

times 510 - ($-$$) db 0
dw 0xaa55

