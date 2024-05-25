GLOBAL sys_time_front_asm
GLOBAL sys_registers_front_asm
GLOBAL sys_read_front_asm
GLOBAL sys_write_front_asm

;TODO: VER COMO PASAMOS LOS PARAMETROS, SI LOS HACEMOS A TRAVES DE RAX, RBX, RCX, RDX O METEMOS CUALQUIERA.
;TODO: el archivo tendria que estar en UserLand, que es el front, pero x problemas con el MakeFile lo puse aca para que ande

section .text

sys_time_front_asm:
        push rbp
        mov rbp, rsp
        mov rdi, 3
        int 80h
        mov rsp, rbp
        pop rbp
        ret

sys_registers_front_asm:
        push rbp
        mov rbp, rsp
        mov rdi, 4
        int 80h
        mov rsp, rbp
        pop rbp
        ret

sys_write_front_asm:
        push rbp
        mov rbp, rsp
        mov rcx, rdx
        mov rdx, rsi
        mov rsi, rdi
        mov rdi, 2
        int 80h
        mov rsp, rbp
        pop rbp
        ret