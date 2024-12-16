section .data

matrix db 1, 2, 3, 4, 5, 6, 7, 8, 9 ; 3x3 matrix
rows equ 3
cols equ 3


section .text
global  _start

_start:
    ; Calculate index: (row * cols) + col
    mov eax, 1         ; Row index (1)
    mov ecx, cols      ; Number of columns (3)
    mul ecx            ; eax = row * cols
    add eax, 2         ; eax = (row * cols) + column (2)

    ; Access matrix[eax]
    lea ebx, [matrix]  ; Load base address of the matrix
    mov al, [ebx + eax] ; Get the element (matrix[1][2])

    ; Modify the element
    mov byte [ebx + eax], 42 ; Set matrix[1][2] = 42

    ; Exit program
    mov eax, 1          ; syscall: exit
    xor ebx, ebx        ; status 0
    int 0x80
