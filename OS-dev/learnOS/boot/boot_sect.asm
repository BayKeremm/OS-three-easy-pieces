; A boot sector that boots a C kernel in 32-bit protected mode (taken from the book)
[org 0x7c00]
KERNEL_OFFSET equ 0x1000        ; Memory offset to which we will load our kernel

mov [BOOT_DRIVE], dl            ; BIOS stores our boot drive in DL, so it's best to
                                ; remember this for later

mov bp, 0X9000                  ; set up the stack
mov sp, bp                      

mov bx, MSG_REAL_MODE           ; Anounce that we are starting booting from 
call print_string               ;   16-bit real mode

call load_kernel                ; Load the kernel

call switch_to_pm               ; switch to protected mode, from which we will not return

jmp $

%include "./my_print_function.asm"
%include "./gdt.asm"
%include "./load_from_drive.asm"
%include "./print_string_pm.asm"
%include "./switch_to_pm.asm"

[bits 16]

load_kernel:
    mov bx, MSG_LOAD_KERNEL     ; print message that we are loading the kernel
    call print_string

    mov bx, KERNEL_OFFSET       ; Set-up paramteres for our disk_load routine
    mov dh, 15                  ; so that we load the first 15 sectors (excluding the boot sector)
    mov dl, [BOOT_DRIVE]        ; from the boot disk to address KERNEL_OFFSET
    call disk_load

    ret

[bits 32]
; This is where we arrive after switching to andd initializing the protected mode
BEGIN_PM:
    mov ebx, MSG_PROT_MODE      ; Use our 32-bit print routine
    call print_string_pm        ; to announce we are in protected mode

    call KERNEL_OFFSET          ; Now jump to the address of our loaded
                                ; kernel code
    jmp $

; global variables
BOOT_DRIVE  db 0
MSG_REAL_MODE   db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE   db "Successfully landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; boot sector padding
times 510-($-$$) db 0
dw 0xaa55