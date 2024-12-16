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
