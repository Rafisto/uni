; Rafał Włodarczyk
; Lab 5.ex1
; I proudly present an x86 program to:
; - Retrieve an integer in text form from standard input (e.g., “12345”)
; - Calculate the sum of the digits of this number (in the example: 1 + 2 + 3 + 4 + 5 = 15)
; - Display the result on the standard output

section .data ; rodata section

    msg    db  'Enter a number: ', 0
    msglen equ $-msg

section .bss ; block started by symbol (uninitialized data)

    buffer resb 100
    bufferlen equ $-buffer

section .text

global  _start

_start:
    ; print the message
    mov edx, msglen
    mov ecx, msg
    mov ebx, 1
    mov eax, 4
    int 80h

    ; read the input
    mov edx, bufferlen
    mov ecx, buffer
    mov ebx, 0
    mov eax, 3
    int 80h

    ; convert to integer
    mov  eax, buffer
    call atoi

    call sum_of_digits
    call iprint
    call newline

    ; exit
    mov eax, 1 ; syscall_exit
    mov ebx, 0 ; exit code = 0
    int 0x80

; ---
; int atoi, eax = pointer to string
; Ascii to integer function (atoi)
atoi:
    push ebx
    push ecx
    push edx
    push esi
    mov  esi, eax
    mov  eax, 0
    mov  ecx, 0
 
.multiplyLoop:
    xor ebx, ebx
    mov bl,  [esi+ecx]
    cmp bl,  48
    jl  .finished
    cmp bl,  57
    jg  .finished
 
    sub bl,  48
    add eax, ebx
    mov ebx, 10
    mul ebx
    inc ecx
    jmp .multiplyLoop
 
.finished:
    cmp ecx, 0
    je  .restore
    mov ebx, 10
    div ebx
 
.restore:
    pop esi
    pop edx
    pop ecx
    pop ebx
    ret

; ---
; int sum_of_digits, eax = integer
; Sum of digits function
sum_of_digits:
    push ebx
    push ecx
    push edx
    push esi
    mov  esi, eax
    mov  edi, 0

.sumLoop:
    mov eax, esi
    mov edx, 0
    mov ecx, 10
    div ecx
    add edi, edx
    mov esi, eax
    cmp esi, 0
    jnz .sumLoop

.restore:
    mov eax, edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    ret  

; ---
; void iprint, eax = integer
; Integer printing function (itoa)
; @see sprint
iprint:
    push eax
    push ecx
    push edx
    push esi
    mov  ecx, 0
 
divideLoop:
    inc  ecx
    mov  edx, 0
    mov  esi, 10
    idiv esi
    add  edx, 48
    push edx
    cmp  eax, 0
    jnz  divideLoop
 
printLoop:
    dec  ecx
    mov  eax, esp
    call sprint
    pop  eax
    cmp  ecx, 0
    jnz  printLoop
 
    pop esi
    pop edx
    pop ecx
    pop eax
    ret
 
; ---
; void newline
; prints a newline
newline:
    mov  eax, 0Ah
    push eax
    mov  eax, esp
    call sprint
    pop  eax
    ret
 
; ---
; int slen, eax = pointer to string
; calculate the length of a string
slen:
    push ebx
    mov  ebx, eax
 
nextchar:
    cmp byte [eax], 0
    jz  finished
    inc eax
    jmp nextchar
 
finished:
    sub eax, ebx
    pop ebx
    ret
 
; ---
; void sprint, eax = pointer to string
; prints a string to stdout
sprint:
    push edx
    push ecx
    push ebx
    push eax
    call slen
 
    mov edx, eax
    pop eax
 
    mov ecx, eax
    mov ebx, 1
    mov eax, 4
    int 80h
 
    pop ebx
    pop ecx
    pop edx
    ret
