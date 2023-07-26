print_string:
    pusha                ; Save the registers

    mov ah, 0x0e         ; Function code for teletype output
    mov al, [bx]         ; Load the first character into AL

.print_loop:
    cmp al, 0            ; Check if the character is null (end of string)
    je .print_end        ; If so, end printing

    int 0x10             ; BIOS interrupt to print the character
    inc bx               ; Move to the next character
    mov al, [bx]         ; Load the next character into AL
    jmp .print_loop      ; Continue printing

.print_end:
    popa                 ; Restore the registers
    ret                  ; Return from the function
