; ---
; int sumAll
; eax = pointer to the array
; ebx = number of elements in the array
; sum all elements of the matrix
sumAll:
    xor edx, edx
    mov ecx, eax

.loop:
    add dl,  [ecx]
    add ecx, 1
    sub ebx, 1
    jnz .loop

.final:
    mov eax, edx
    ret

exit:
    mov eax, 1
    mov ebx, 0
    int 80h

; ---
; int sumDiagonal
; eax = pointer to the array
; ebx = number of elements in the array
; sum all elements of the main diagonal
sumDiagonal:
    xor edx, edx
    mov ecx, eax

    add dl, [ecx]

    add ecx, 4
    add dl,  [ecx]

    add ecx, 4
    add dl,  [ecx]

    mov eax, edx
    ret
