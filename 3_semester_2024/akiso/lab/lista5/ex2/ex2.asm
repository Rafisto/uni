; Rafał Włodarczyk
; Lab 5.ex2
; I proudly present an x86 program to:
; - take as input a 3x3 matrix (9 integers, stored in program memory).
; - calculate the sum of all elements of the matrix and the sum of the elements on the main diagonal.
; - displays both results on standard output
;        Sum of elements: X
;        Sum of diagonal: Y

%include "print.asm"
%include "atoi.asm"
%include "sum.asm"

section .rodata

    msg_sumall  db "Sum of elements: ", 0Ah, 0
    msg_sumdiag db "Sum of diagonal: ", 0Ah, 0

section .data

    matrix db 0,0,0\
              ,0,0,0\
              ,0,0,0 ; 3x3 matrix

section .bss
    
    buffer resb 100 ; reserve 100 bytes for the buffer
    bufferlen equ $-buffer ; length of the buffer

section .text

global  _start

_start:
    mov  eax, matrix
    call readMatrix

    mov  eax, matrix
    mov  ebx, 9
    call sumAll

    push eax

    mov  eax, msg_sumall
    call sprint

    pop eax

    call iprint
    call newline

    mov  eax, matrix
    call sumDiagonal

    push eax

    mov  eax, msg_sumdiag
    call sprint

    pop eax

    call iprint
    call newline

    jmp exit

readMatrix:
    mov edi, matrix
    mov esi, 9

.loop:
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, bufferlen
    int 80h

    mov  eax, buffer
    call atoi

    mov [edi], eax

    add edi, 1
    sub esi, 1
    jnz .loop
    
    ret

