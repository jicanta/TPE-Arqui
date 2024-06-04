GLOBAL test00

section .text

; ver foto de cuales estan bien y cuales mal, anda medio falopa
test00:
    mov rax, 01h
    mov rbx, 02h
    mov rcx, 03h
    mov rdx, 04h
    mov rsi, 05h
    mov rdi, 06h
    ; el rbp no lo quiero modificar
    ; el rsp tampoco
    mov r8, 08h
    mov r9, 09h
    mov r10, 10h
    mov r11, 11h
    mov r12, 12h
    mov r13, 13h
    mov r14, 14h
    mov r15, 15h

    mov rdx, 0
    mov rcx, 0
    div rcx      ; TODO: el problema es que no me deja compilarlo si pongo div 0 lol como lo pruebo

	ret
