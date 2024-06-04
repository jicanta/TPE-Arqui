GLOBAL test06

section .text
test06:
    db 0xFF, 0xFF, 0xFF, 0xFF       ; invalid op code bytes
    nop
    mov eax, 1
    xor ebx, ebx
    int 80h
    ret
