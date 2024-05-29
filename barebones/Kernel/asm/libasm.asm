GLOBAL cpuVendor
GLOBAL inPIT
GLOBAL outPIT

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

inPIT:
       push rbp
       mov rbp, rsp
       
       mov rdx, rdi
       in al, dx
       
       mov rsp, rbp
       pop rbp
       ret

outPIT:
       push rbp
       mov rbp, rsp
       
       mov rax, rsi
       mov rdx, rsi
       out dx, al
       
       mov rsp, rbp
       pop rbp
       ret
