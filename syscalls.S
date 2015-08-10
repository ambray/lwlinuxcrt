bits 64

global lw_read, lw_write, lw_open, lw_close, lw_lseek, lw_mmap, lw_mprotect, lw_munmap, lw_brk

; ssize_t lw_read(unsigned int fd, char* buf, size_t count)
lw_read:
	xor rax, rax
	syscall
	ret

; ssize_t lw_write(unsigned int fd, const char* buf, size_t count)
lw_write:
	mov rax, 0x01
	syscall
	ret

; unsigned int lw_open(const char* fname, int flags, int mode)
lw_open:
	mov rax, 0x02
	syscall
	ret

; int lw_close(unsigned int fd)
lw_close:
	mov rax, 0x03
	syscall
	ret

; ssize_t lw_lseek(int fd, ssize_t offset, int whence)
lw_lseek:
	mov rax, 0x08
	syscall
	ret

; void* lw_mmap(unsigned long addr, unsigned long len, unsigned long prot, 
;		 	    unsigned long flags, unsigned long fd, unsigned long offset)
lw_mmap:
	mov rax, 0x09
	syscall
	ret

; int lw_mprotect(unsigned long start, size_t len, unsigned long prot)
lw_mprotect:
	mov rax, 0x0a
	syscall
	ret

; int lw_munmap(unsigned long addr, size_t len)
lw_munmap:
	mov rax, 0x0b
	syscall
	ret

; void* lw_brk(unsigned long brk)
lw_brk:
	mov rax, 0x0c
	syscall
	ret