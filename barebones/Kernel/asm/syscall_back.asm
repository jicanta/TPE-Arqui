GLOBAL sys_time_asm
GLOBAL sys_read_asm
GLOBAL sys_write_asm
GLOBAL sys_registers_asm

EXTERN sys_time
EXTERN sys_peekRegisters
EXTERN sys_write
EXTERN sys_read

section .text

sys_time_asm:
        push rbp
        mov rbp, rsp
        call sys_time
        mov rsp, rbp
        pop rbp
        ret

sys_registers_asm:
        push rbp
        mov rbp, rsp
        call sys_peekRegisters
        mov rsp, rbp
        pop rbp
        ret

sys_write_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size 
        push rbp
        mov rbp, rsp
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_write
        mov rsp, rbp
        pop rbp
        ret

sys_read_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size
        push rbp
        mov rbp, rsp
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_read
        mov rsp, rbp
        pop rbp
        ret