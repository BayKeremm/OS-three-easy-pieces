[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; prints a null-terminated string pointed to by EbX
print_string_pm:
    pusha                       ; push all register values to the stack
    mov edx, VIDEO_MEMORY       ; set edx to the start of vid mem

print_string_pm_loop:
    mov al, [ebx]               ; store the char at ebx in al
    mov ah, WHITE_ON_BLACK      ; store the attributes in ah

    cmp al, 0                   ; end of the string ?
    je print_string_pm_done

    mov [edx], ax               ; store char and attributes at current char cell

    add ebx, 1                  ; increment ebx to the next char in string
    add edx, 2                  ; move to the next char cell in vid memory

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret