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