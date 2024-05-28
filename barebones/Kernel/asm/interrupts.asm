GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL irq00                ; timer tick interruption
GLOBAL irq01                ; keyboard interruptionn
GLOBAL exception00          ; exception 00 (division by zero)
GLOBAL exception06          ; exception 06 (invalid op code)
GLOBAL sys_call
GLOBAL registerSnapshot

EXTERN irqHandler           ; function in IRQs.c which handles interruption
EXTERN exceptionHandler     ; function in exceptions.c which handles exceptions
EXTERN syscallHandler		; function is syscalls.c which handles syscalls

EXTERN getRegisters

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

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqHandler                    ; calling irqHandler to process interruption

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionHandler             ; calling exceptionHandler to process interruption

	popState
	iretq
%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret

_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

; timer tick
irq00:
	irqHandlerMaster 0

; keyboard
irq01:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

; division by zero exception
exception00:

	pushState
	mov rdi, 0
	call exceptionHandler
	popState
	iretq

; invalid op code exception
exception06:

	pushState
	mov rdi, 6
	call exceptionHandler
	popState
	iretq

sys_call:
	pushState
	call syscallHandler
	popState
	iretq

haltcpu:
	cli
	hlt
	ret

registerSnapshot:
		pushState
		mov QWORD [registers], 545
		mov QWORD[registers + 8 * 1], 545
		mov QWORD[registers + 8 * 2], 545
		mov QWORD[registers + 8 * 3], 545
		mov [registers + 8 * 4], rbp
		mov [registers + 8 * 5], rdi
		mov [registers + 8 * 6], rsi   
		mov rax, [rsp+18*8]
		mov [registers + 8 * 7], rax       ;inserto rsp
		mov rax, [rsp+15*8] 
		mov [registers + 8 * 8], rax      ;inserto rip
		mov [registers + 8 * 9], r8
		mov [registers + 8 * 10], r9
		mov [registers + 8 * 11], r10
		mov [registers + 8 * 12], r11
		mov [registers + 8 * 13], r12
		mov [registers + 8 * 14], r13
		mov [registers + 8 * 15], r14
		mov [registers + 8 * 16], r15

		mov rdi, registers    ; TODO: no estoy seguro de que este pasando bien los parametros
		popState
		ret

SECTION .bss
	aux resq 1
	registers resq 17
 
