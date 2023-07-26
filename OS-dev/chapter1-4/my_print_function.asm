;my_print_function:
    ;pusha           ; push all register values to the stack
    ;mov ah, 0x0e    ; int = 10/ ah=0x0e -> BIOS tele-type output
    ;mov al, [bx]
    ;cmp al, 0
    ;je .done
    ;int 0x10
    ;add bx, 1
    ;jmp my_print_function
;.done:
    ;popa            ; restore original register values before returning 
    ;ret
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
