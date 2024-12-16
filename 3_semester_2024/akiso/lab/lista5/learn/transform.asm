section .data
    result db 0        ; To store the result

section .text
    global _start

_start:
    mov eax, 214        ; x = 214
    call calculate_f    ; Call the function

    ; Store the result in memory
    mov [result], al

    ; Exit the program
    mov eax, 60         ; syscall: exit
    xor edi, edi        ; status: 0
    syscall

calculate_f:
    ; Input: eax contains x
    ; Output: eax will contain the result of f(x)

    ; Step 1: Divide x by 320
    mov ebx, 320        ; Divisor
    cdq                 ; Sign-extend EAX into EDX:EAX
    idiv ebx            ; EAX = x / 320

    ; Step 2: Multiply the result by 3
    imul eax, eax, 3    ; EAX = EAX * 3

    ; Step 3: Subtract 2
    sub eax, 2          ; EAX = EAX - 2

    ret
