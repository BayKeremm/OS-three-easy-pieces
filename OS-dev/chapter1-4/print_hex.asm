; Ascii '0'-'9' = hex 0x30-0x39
; Ascii 'A'-'F' = hex 0x41-0x46
; Ascii 'a'-'f' = hex 0x61-0x66


print_hex:
    pusha
    mov cx, 0           ; initialize the loop counter

hex_loop:
    cmp cx, 4           ; are we done with the loop ? 
    je end_hex_loop

    ; convert dx hex values to ascii
    mov ax, dx          ; copy dx (input) to ax
    and ax, 0x000F      ; keep the final digit to convert to ascii
    add al, 0x30        ; get ascii number or letter value
    cmp al, 0x39        ; is hex value 0-9 (<= 0x39) or A-F (> 0x39)
    jle move_into_bx
    add al, 0x07        ; to get ascii 'A'-'F'

move_into_bx:
    mov bx, HEX_OUT + 5 ; Base address of HEX_OUT + length of the string
    sub bx, cx          ; substract loop counter
    mov [bx], al        ; copy al to the content of the address bx
    ror dx, 4           ; rotate right by 4 bits
                        ; 0x12AB -> 0xB12A -> 0xAB12 -> 0x2AB1 -> 0x12AB
    add cx, 1           ; increment the loop counter
    jmp hex_loop        ; loop for the next hex digit in dx

end_hex_loop:
    mov bx, HEX_OUT
    call print_string
    popa
    ret

HEX_OUT: db '0x0000', 0