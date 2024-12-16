; nasm program to:
; - sieve of eratosthenes from 2 to 100_000

%include "print.asm"

section .data
    msg db "Prime numbers from 2 to 100_000:", 0Ah, 0
    msglen equ $-msg

    primes db 100_000 dup(0)
    primeslen equ $-primes

section .text

global _start
_start:
    ; Print the initial message
    mov eax, msg
    call sprint

    ; Initialize the primes array
    mov ecx, 100000
    xor edi, edi
init_loop:
    mov byte [primes + edi], 1
    inc edi
    loop init_loop

    ; Sieve of Eratosthenes algorithm
    mov ecx, 2
sieve_loop:
    mov eax, ecx
    mul ecx
    cmp eax, 100000 ; (can lower to sqrt(100_000)
    ja end_sieve
    mov edi, eax
mark_multiples:
    mov byte [primes + edi], 0
    add edi, ecx
    cmp edi, 100000
    jb mark_multiples
    inc ecx
    jmp sieve_loop
end_sieve:

    ; Print the prime numbers
    mov ecx, 2
print_primes:
    cmp ecx, 100000
    ja end_program
    mov al, [primes + ecx]
    test al, al
    jz not_prime
    mov eax, ecx
    call iprint
    call newline
not_prime:
    inc ecx
    jmp print_primes

end_program:
    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80