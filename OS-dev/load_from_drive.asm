disk_load:
    push dx         ; store dx on stack so later we can recall
                    ; how many sectors were requested to be read

    mov ah, 0x02    ; BIOS read sector function
    mov al, dh      ; Read dh sectors
    mov ch, 0x00    ; select cylinder 0
    mov dh, 0x00    ; select head 0
    mov cl, 0x02    ; Start reading from second sector

    int 0x13

    jc disk_error   ; jump if error (carry flag set)

    pop dx          ; restore dx from the stack
    cmp dh, al      ; if al (sectors to read) != dh (sectors expected)
    jne disk_error  ; display error message
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG: db "Disk read error!", 0

