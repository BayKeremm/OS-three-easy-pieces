mov ah, 0x0e            ; teletype BIOS routine

mov al, [the_secret]
int 0x10                ; does this print X no

mov bx, 0x7c0           ; cant set ds directly
mov ds, bx
mov al, [the_secret]
int 0x10                ; does this print X yes

mov al, [es:the_secret]
int 0x10                ; does this print X no

mov bx, 0x7c0           ; cant set ds directly
mov es, bx
mov al, [es:the_secret]
int 0x10                ; does this print X yes

jmp $

the_secret:
    db "X"

times 510-($-$$) db 0
dw 0xaa55