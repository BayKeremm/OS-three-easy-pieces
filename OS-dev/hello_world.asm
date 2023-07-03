[org 0x7c00]            ; tells the assembler where this code will be loaded

mov bx, HELLO_MSG
call print_string

mov bx, GOODBYE_MSG
call print_string

mov dx, 0x12AB
call print_hex

jmp $

%include "my_print_function.asm"
%include "printhex.asm"

HELLO_MSG:
    db 'Hello, World!', 0

GOODBYE_MSG:
    db 'Goodbye!', 0

times 510-($-$$) db 0
dw 0xaa55