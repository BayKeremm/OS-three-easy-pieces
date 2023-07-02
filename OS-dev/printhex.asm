[org 0x7c00]            ; tells the assembler where this code will be loaded

mov dx, 0x1fb6
call print_hex

jmp $

%include "my_print_function.asm"

print_hex:
    pusha               ; save all register values
    mov cx, 4           ; start the counter: we want to print 4 characters
    
char_loop:
    dec cx
    mov ax, dx          ; copy dx into ax 
    shr dx, 4           ; shift dx 4 bits to the right
    



    mov bx, HEX_OUT
    call print_string
    ret

HEX_OUT: db '0x0000', 0

times 510-($-$$) db 0
dw 0xaa55