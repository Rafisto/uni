section .text

global  _start

_start:
    mov  eax, 12345
    call sum_of_digits

    ; print the sum of digits
    call iprint

    ; exit
    mov eax, 1 ; syscall_exit
    mov ebx, 0 ; rc = 0
    int 80h

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
