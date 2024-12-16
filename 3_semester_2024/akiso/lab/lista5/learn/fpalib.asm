section .data
    rows  dd 320
    cols  dd 200
    max_i dd 254
    in_x  dd 180
    in_y  dd 100

    scal_mul_x dd 3.0
    scal_sub_x dd 2.0

    scal_mul_y dd 2.0
    scal_sub_y dd 1.0

    xtemp dd 0.0
    x     dd 0.0
    x0    dd -0.659986137
    x2    dd 0.0
    y     dd 0.0
    y0    dd -0.550827281 
    y2    dd 0.0
    i     dd 0

    four dd 4.0
    two  dd 2.0

section .text
global  _start

_start:
    ; mov eax, in_x
    ; call conv_x_to_mandelbrot_space

    ; mov eax, in_y
    ; call conv_y_to_mandelbrot_space

    call mandelbrot_color_loop

    ; Exit program
    jmp exit

exit:
    mov eax, 1   ; syscall: exit
    xor ebx, ebx ; status 0
    int 0x80

; ---
; float conv_x_to_mandelbrot_space, eax = p,
; ret eax = p / 320 * 3.5 - 2.5 
conv_x_to_mandelbrot_space:
    fld  dword [eax]
    fld  dword [rows]
    fdiv
    fld  dword [scal_mul_x]
    fmul
    fld  dword [scal_sub_x]
    fsub
    fstp dword [x0]
    ret

; ---
; float conv_y_to_mandelbrot_space, eax = p,
; ret eax = p / 200 * 2 - 1
conv_y_to_mandelbrot_space:
    fld  dword [eax]
    fld  dword [cols]
    fdiv
    fld  dword [scal_mul_y]
    fmul
    fld  dword [scal_sub_y]
    fsub
    fstp dword [y0]
    ret

; ---
; for each pixel (Px, Py) on the screen do
;     x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
;     y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
;     x := 0.0
;     y := 0.0
;     iteration := 0
;     max_iteration := 1000
;     while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
;         xtemp := x*x - y*y + x0
;         y := 2*x*y + y0
;         x := xtemp
;         iteration := iteration + 1
 
;     color := palette[iteration]
;     plot(Px, Py, color)
; Method to calculate x^2
mandelbrot_color_loop:
    mov dword [xtemp], 0
    mov dword [x],     0
    mov dword [x2],    0
    mov dword [y],     0
    mov dword [y2],    0
    mov dword [i],     0

.loop_start:
    ; Squaring x and storing in x2
    fld  dword [x]  ; Load x
    fmul st0, st0   ; Square x
    fstp dword [x2] ; Store x^2 in x2

    ; Squaring y and storing in y2
    fld  dword [y]  ; Load y
    fmul st0, st0   ; Square y
    fstp dword [y2] ; Store y^2 in y2

    ; Checking escape condition (x^2 + y^2 > 4)
    xor    eax, eax        ; Clear eax
    fld    dword [x2]      ; Load x^2
    fld    dword [y2]      ; Load y^2
    fadd                   ; Add x^2 + y^2
    fld    dword [four]    ; Load 4
    fcomip st0, st1        ; Compare (x^2 + y^2) with 4
    fstsw  ax              ; Store status word
    sahf                   ; Transfer status to flags
    ja .escape_not_met

    ; If escape condition is met, jump to .loop_end
    jmp .loop_end

.escape_not_met:
    ; Compare iteration count (i) with max_i
    mov eax, [i]
    mov ebx, [max_i]
    cmp eax, ebx
    jg  .loop_end    ; If i >= max_i, jump to .loop_end

    ; Calculating new x value (x_new = x^2 + y^2 + x0)
    fld  dword [x]     ; Load x
    fmul st0, st0      ; Square x
    fld  dword [y]     ; Load y
    fmul st0, st0      ; Square y
    fadd               ; Add x^2 + y^2
    fadd dword [x0]    ; Add x0
    fstp dword [xtemp] ; Store result in xtemp

    ; Calculating new y value (y_new = 2*x*y + y0)
    fld  dword [x]   ; Load x
    fmul dword [y]   ; Multiply x * y
    fmul dword [two] ; Multiply by 2
    fadd dword [y0]  ; Add y0
    fstp dword [y]   ; Store result in y

    ; Updating x value (x = xtemp)
    mov eax,       [xtemp] ; Load xtemp into eax
    mov dword [x], eax     ; Store it back into x

    ; Increment iteration count
    inc dword [i]
    jmp .loop_start ; Jump to the next iteration of the loop

.loop_end:
    mov eax, [i] ; Load iteration count into eax
    ret
