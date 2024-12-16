; nasm program to read a text input

section .data ; data section
    msg    db  'Enter a string: ', 0
    msglen equ $-msg                 ; length of the message

section .bss ; bss means block started by symbol (uninitialized data)
    buffer resb 100 ; reserve 100 bytes for the buffer
    bufferlen equ $-buffer ; length of the buffer

section .text
global  _start

_start:
    ; write enter a string
    mov edx, msglen ; length of the message
    mov ecx, msg    ; pointer to the message
    mov ebx, 1      ; file descriptor 1 (stdout)
    mov eax, 4      ; write syscall
    int 80h

    ; read the input
    mov edx, bufferlen ; length of buffer
    mov ecx, buffer    ; buffer to read into
    mov ebx, 0         ; file descriptor 0 (stdin)
    mov eax, 3         ; read syscall
    int 80h

    ; print the input
    mov edx, bufferlen ; length of the buffer
    mov ecx, buffer    ; pointer to the buffer
    mov ebx, 1         ; file descriptor 1 (stdout)
    mov eax, 4         ; write syscall
    int 80h

    ; exit
    mov eax, 1 ; syscall_exit
    mov ebx, 0 ; exit code = 0
    int 0x80