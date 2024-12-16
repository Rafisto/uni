section .data

message db 'The length of this message will resolve dynamically, while the print is called.', 0Ah, 0h

section .text

global _start

_start:
    mov eax, message
    call sprint

    jmp exit

;------------------------------------------
; int slen(String message)
; String length calculation function
slen:
    push    ebx
    mov     ebx, eax
 
nextchar:
    cmp     byte [eax], 0
    jz      finished
    inc     eax
    jmp     nextchar
 
finished:
    sub     eax, ebx
    pop     ebx
    ret
 
 
;------------------------------------------
; void sprint(String message)
; String printing function
sprint:
    push    edx
    push    ecx
    push    ebx
    push    eax
    call    slen
 
    mov     edx, eax
    pop     eax
 
    mov     ecx, eax
    mov     ebx, 1
    mov     eax, 4
    int     80h
 
    pop     ebx
    pop     ecx
    pop     edx
    ret  

exit:
    mov eax, 1 ; syscall_exit
    mov ebx, 0 ; exit code = 0
    int 0x80