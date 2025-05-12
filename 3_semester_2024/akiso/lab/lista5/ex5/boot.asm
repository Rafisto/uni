; nasm -fbin boot.asm
; qemu-system-i386 -drive format=raw,file=boot

bits 16
org  0x7c00

; Bas Parameters of the simulation
; Canvas size (VGA Mode 13h)
rows       dd 320.0
cols       dd 200.0
last_addr  dd 0xFC80

; Max interations per pixel
max_i      dw 16

; Frame of reference (map 320,200 to [-2.0, 0.475] x [-1.125, 1.125])
; x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.475))
; y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.125, 1.125))
x_min      dd -2.0
x_max      dd 0.475
y_min      dd -1.125
y_max      dd 1.125
x_offset   dd -2.0
y_offset   dd 1.1

; Increments for the frame of reference
x_incr     dd 0.0    ; assigned automatically
y_incr     dd 0.0    ; assigned automatically

; Variables for the Mandelbrot set generation
x_loc_temp dd 0.0
x_loc      dd 0.0
y_loc      dd 0.0

; Constants for the Mandelbrot set generation
two        dd 2.0
four       dd 4.0

boot:
	mov ax, 0x2401 ; Enable A20, access to memory above the first 1 MB in x86 real mode.
	int 0x15
	mov ax, 0x13 ; VGA Mode 13h
	int 0x10

	push 0xA000
	pop  es

	xor eax, eax
	xor ebx, ebx
	xor edx, edx
	xor ecx, ecx
	xor edi, edi
	xor esi, esi

; ---
; void calc_increments
; 
; takes [x_min], [x_max], [y_min], [y_max], [rows], [cols] (all must be floats) 
; and performs x87 FPU operations to calculate x_incr and y_incr
calc_increments:
    ; calc x_incr
    fld  dword [x_max]
    fld  dword [x_min]
    fsub               
    fld  dword [rows]
    fdiv                
    fstp dword [x_incr]

    ; calc y_incr
    fld  dword [y_max]
    fld  dword [y_min]
    fsub               
    fld  dword [cols]
    fdiv               
    fstp dword [y_incr]

mandelbrot_begin:
    ; reset i, x_temp, y_temp
	xor ebx,           ebx
	mov dword [x_loc], 0x0
	mov dword [y_loc], 0x0

; ---
; void mandelbrot
;
; for each pixel (Px, Py) on the screen do
;   x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
;   y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
;   x := 0.0
;   y := 0.0
;   iteration := 0
;   max_iteration := 1000
;   while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
;       xtemp := x*x - y*y + x0
;       y := 2*x*y + y0
;       x := xtemp
;       iteration := iteration + 1
;   color := palette[iteration]
;   plot(Px, Py, color)
; 
; Source: https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
mandelbrot_color:
    ; check i == max_i (end of loop)
	cmp bx, [max_i]
	je  out_of_iterations

    ; xtemp := x*x - y*y + x0
	fld  dword [x_loc]
	fmul dword [x_loc]
	fld  dword [y_loc]
	fmul dword [y_loc]
	fsubp                  
	fadd dword [x_offset]
	fstp dword [x_loc_temp]

    ; y := 2*x*y + y0
	fld  dword [two]
	fmul dword [x_loc]
	fmul dword [y_loc]
	fadd dword [y_offset]
	fstp dword [y_loc]
	
    ; x := xtemp
	push dword [x_loc_temp]
	pop  dword [x_loc]

    ; comparison
	; x*x + y*y ≤ 2*2
	fld  dword [y_loc]
	fmul dword [y_loc]
	fld  dword [x_loc]
	fmul dword [x_loc]
	faddp              
	fld  dword [ four]

    ; comparison result
	fcompp                  ; Compare ST(0) and ST(1) and pop both
	fstsw  ax               ; Store comparison flags in ax
	inc    ebx              ; Increment i
	sahf                    ; Set flags in FLAGS register
	jnc    mandelbrot_color ; Continue if ST(0) <= ST(1) i.e. if 2 * x_loc * y_loc + b <= 4
	
    add bl,      16 ; start from grayscale
	mov [es:di], bl ; Place resulting color into memory address
	jmp continue

out_of_iterations:
	mov byte [es:di], 0
    jmp continue

continue:
	; Move to the next pixel
	inc di
	inc cx

    ; Check if (x,y) > (320,200)
	cmp di, [last_addr]
	je  exit
	
	; Step on x-axis
	fld  dword [x_incr]
	fadd dword [x_offset]
	fstp dword [x_offset]

	; Determine whether a new row has been reached
	cmp cx, 320
	jne mandelbrot_begin

	inc dx
	xor cx, cx

    ; Reset on x-axis
	push dword [x_min]
	pop  dword [x_offset]

	; Step on y-axis
	fld  dword [y_offset]
	fsub dword [y_incr]
	fstp dword [y_offset]

	jmp mandelbrot_begin
			
exit:
	cli
	hlt

times 510 - ($-$$)  db  0
dw 0xaa55