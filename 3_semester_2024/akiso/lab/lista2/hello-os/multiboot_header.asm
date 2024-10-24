; Multiboot 2 - Compliant Header
; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html (Section 3.1.1)
section .multiboot_header
header_start:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_HEADER_ARCH       equ 0         ; 32-bit (protected) mode of i386
    MULTIBOOT_HEADER_MAGIC	equ 0xe85250d6          ; magic number
    MULTIBOOT_CHECKSUM	equ - (MULTIBOOT_HEADER_MAGIC + (header_end - header_start))  ; checksum
                                                        ; (magic number + checksum + flags should equal 0)

    MULTIBOOT_TYPE		equ 0
    MULTIBOOT_FLAGS		equ 0
    MULTIBOOT_SIZE		equ 8

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_ARCH
    dd header_end - header_start ; Size of the Header
    dd MULTIBOOT_CHECKSUM

    ; Required end tag
    dw MULTIBOOT_TYPE
    dw MULTIBOOT_FLAGS
    dd MULTIBOOT_SIZE
header_end:
