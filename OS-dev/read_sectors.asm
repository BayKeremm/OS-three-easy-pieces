[org 0x7c00]

    mov [BOOT_DRIVE], dl        ; store the boot drive(dl) in a variable as well

    mov bp, 0x8000              ; set the stack safely out of the way at 0x8000
    mov sp, bp

    mov bx, 0x9000              ; Load 5 sectors to 0x0000(ES):0x9000(BX) from the boot disk
    mov dh, 5
    mov dl, [BOOT_DRIVE]
    call disk_load

    mov dx, [0x9000]            ; print out the first loaded word, which we expect to be 0xdada,
                                ; stored at address 0x9000
    call print_hex

    mov dx, [0x9000 + 512]      ; also print the first word from the 2nd loaded sector: 0xface
    call print_hex

    jmp $

    %include "my_print_function.asm"
    %include "print_hex.asm"
    %include "load_from_drive.asm"

    BOOT_DRIVE: db 0

    times 510 - ($-$$) db 0
    dw 0xaa55

    times 256 dw 0xdada
    times 256 dw 0xface