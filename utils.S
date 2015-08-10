bits 64

extern main

global _start

_start:
	call main
	mov rdi, rax	; get our exit code
	mov rax, 0x3c	; sys_exit
	syscall
	ret
