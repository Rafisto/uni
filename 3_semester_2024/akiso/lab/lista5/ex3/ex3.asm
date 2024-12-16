; nasm program to:
; - Convert an i32 to hexadecimal

%include "print.asm"

section .data
    msg    db  "Enter an integer: ", 0
    msglen equ $-msg

    hex    db  "0x00000000", 0
    hexlen equ $-hex

section .bss

    buffer resb 100
    bufferlen equ $-buffer

section .text
    
global  _start

_start:
    ; Print the message
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msglen
    int 0x80

    ; Read the input
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, bufferlen
    int 0x80

    ; Convert input string to integer
    mov esi, buffer
    xor eax, eax
    xor ebx, ebx

convert_loop:
    movzx ecx, byte [esi] ; load byte from buffer
    cmp   ecx, 0xA        ; check for newline
    je    convert_done    ; if newline, done
    sub   ecx, '0'        ; convert ASCII to integer
    imul eax, eax, 10     ; multiply eax by 10 (put next integer)
    add   eax, ecx        ; add current digit
    inc   esi             ; move to next character
    jmp   convert_loop    ; repeat

convert_done:
    ; Convert integer to hexadecimal string
    mov edi, hex + 2 ; destination index (skip "0x")
    mov ecx, 8       ; number of hex digits

convert_to_hex:
    rol eax, 4    ; rotate by 4 bits
    mov ebx, eax  ; copy eax
    and ebx, 0xF  ; mask lower 4 bits
    add bl,  '0'  ; convert to ASCII
    cmp bl,  '9'  ; check if greater than '9'
    jbe store_hex ; if less or equal, store
    add bl,  7    ; adjust for 'A'-'F'

store_hex:
    mov  [edi], bl      ; store hex digit
    inc  edi            ; move to next position
    loop convert_to_hex ; repeat for all digits

    mov  eax, hex
    call sprint

    call newline

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80