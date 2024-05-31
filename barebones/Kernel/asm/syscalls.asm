
GLOBAL sys_read_asm
GLOBAL sys_write_asm
GLOBAL sys_time_asm
GLOBAL sys_registers_asm
GLOBAL sys_getkeypressed_asm
GLOBAL sys_fillrect_asm
GLOBAL sys_write_at_asm
GLOBAL sys_write_color_asm
GLOBAL sys_write_color_at_asm
GLOBAL sys_sleep_asm

EXTERN sys_read
EXTERN sys_write
EXTERN sys_time
EXTERN sys_peekRegisters
EXTERN sys_getkeypressed
EXTERN sys_fillrect
EXTERN sys_write_at
EXTERN sys_write_color
EXTERN sys_write_color_at
EXTERN sys_sleep

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

sys_read_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size
        pushState
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_read
        popState
        ret

sys_write_asm:    ; en rdi:id, rsi:fd, rdx:buff, rcx: size 
        pushState
        mov rdi, rsi
        mov rsi, rdx
        call sys_write
        popState
        ret

sys_getkeypressed_asm:
		pushState
        mov rdi, rsi
        mov rsi, rdx
        call sys_getkeypressed
        popState
        ret
		
sys_fillrect_asm:
	pushState
    mov rdi, rsi
	mov rsi, rdx
    call sys_fillrect
    popState
    ret

sys_write_at_asm:
		pushState
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
		mov rcx, r8
        call sys_write_at
        popState
        ret

sys_write_color_asm:
		pushState
        mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
        call sys_write_color
        popState
        ret

sys_write_color_at_asm:
		pushState
		mov rdi, rsi
        mov rsi, rdx
        mov rdx, rcx
		mov rcx, r8
		mov r8, r9
        call sys_write_color_at
        popState
        ret

sys_sleep_asm: