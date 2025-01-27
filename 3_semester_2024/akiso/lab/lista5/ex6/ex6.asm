section .data
    fmt db "%s", 0

section .bss
    result resb 65

section .text
    extern printf, scanf
    global _start

_start:
    ; Read input
    push dword result
    push dword fmt
    call scanf
    add esp, 8

    push dword result
    call atoi
    add esp, 4
    mov ebx, eax
    mov rbx, rax
    mov eax, 1
    ; Initialize result to 1
    mov rax, 1

    cmp ebx, 0
    ; Check if rbx is 0
    cmp rbx, 0
    je end_factorial
    imul eax, ebx
    ; Multiply rax by rbx
    imul rax, rbx
    dec ebx
    ; Decrement rbx
    dec rbx

    ; Loop
    jmp factorial_loop

    push dword result
    call itoa
    add esp, 4
    mov rdi, result
    push dword result
    push dword fmt
    call printf
    add esp, 8
    mov rdi, fmt
    mov eax, 1
    xor ebx, ebx
    int 0x80
    ; Exit
    mov rax, 60
    xor rdi, rdi
    xor eax, eax
    xor ecx, ecx
atoi:
    movzx edx, byte [edi + ecx]
    xor rax, rax
    xor rcx, rcx
atoi_loop:
    imul eax, eax, 10
    add eax, edx
    inc ecx
    sub rdx, '0'
    imul rax, rax, 10
    add rax, rdx
    inc rcx
    jmp atoi_loop
atoi_done:
    mov ecx, 10
    xor edx, edx
itoa:
    xor edx, edx
    div ecx
    xor rdx, rdx
    dec edi
    mov [edi], dl
    test eax, eax
    add dl, '0'
    dec rdi
    mov byte [rdi], dl
    test rax, rax
    jnz itoa_loop
    ret