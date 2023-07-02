mov ah, 0x0e

mov bp, 0x8000 ; set the base of the stack a little above where BIOS loads our boot sector
mov sp, bp

push 'A'
push 'B'
push 'C'

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

mov al, [0x7ffe]
int 0x10

jmp $

times 510 - ($-$$) db 0 ;$ is used to refer to the current address and 
                        ;$$ is used to refer to the address of the start of current section in assembly 
dw 0xaa55

