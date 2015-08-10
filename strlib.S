bits 64

global lw_strlen, lw_strnlen, lw_memcpy, lw_memmove, lw_memset, lw_strchr, lw_memcmp 
global lw_memchr, lw_strcmp, lw_strncmp, lw_strcpy, lw_strncpy, lw_strstr

; size_t lw_strlen(char*)
lw_strlen:
  xor rax, rax
  mov rcx, 0xffffffffffffffff
  repne scasb 
  not rcx	  
  dec rcx	  
  mov rax, rcx
  ret

; size_t lw_strnlen(char*, size_t)
lw_strnlen:
	xor rax, rax
	mov rcx, rsi
	repne scasb
	mov rax, rsi
	sub rax, rcx
	mov dl, byte [rdi] 
	cmp dl, 0x00 ; did we hit the end of the string?
	jnz .done
	dec rax
.done:
	ret

; void* lw_memcpy(void* dest, void* src, size_t length)
lw_memcpy:
	mov r8, rdi
	mov rcx, rdx
	rep movsb
	mov rax, r8
	ret

; void* lw_memmove(void* dest, void* src, size_t length)
lw_memmove:
	mov r8, rdi
	mov rcx, rdx
	std
	lea rdi, [rdi + rcx]
	lea rsi, [rsi + rcx]
	rep movsb
	cld
	mov rax, r8
	ret

; void* lw_memset(void* s, unsigned char c, size_t n)
lw_memset:
	mov r8, rdi
	mov rax, rsi
	mov rcx, rdx
	rep stosb
	mov rax, r8
	ret

; char* lw_strchr(char* string, char needle)
lw_strchr:
	mov r8, rdi
	call lw_strlen
	mov rdi, r8
	mov rcx, rax
	mov rax, rsi
	repne scasb
	mov dl, byte [rdi]
	cmp dl, 0x00
	jnz .found
	mov rdi, 0x00 ; needle not found :<
	jmp .done
.found:
	dec rdi ; we are now one position past the place the character was found at
.done:
	mov rax, rdi
	ret


; int lw_memcmp(void* dest, void* src, size_t count)
lw_memcmp:
	mov rcx, rdx
	repe cmpsb
	mov rax, rcx
	ret

; void* lw_memchr(void* haystack, unsigned char needle, size_t count)
lw_memchr:
	mov rax, rsi
	mov rcx, rdx
	repne scasb
	mov dl, byte [rdi - 1]
	cmp dl, al
	jz .found
	mov rdi, 0x00
	jmp .done
.found:
	dec rdi
.done:
	mov rax, rdi
	ret

; int lw_strcmp(const char* s1, const char* s2)
lw_strcmp:
	mov r8, rdi 	; stash the beginning of the string
	call lw_strlen
	mov rdx, rax	; set params up to call memcmp
	mov rdi, r8
	call lw_memcmp
	ret

; int lw_strncmp(const char* s1, const char* s2, size_t count)
lw_strncmp:
	mov r8, rdi
	mov r9, rsi
	mov rsi, rdx
	call lw_strnlen ; need to change this to use the smaller of two string lengths
	mov rdi, r8
	mov rsi, r9
	mov rdx, rax
	call lw_memcmp
	ret

; char* lw_strcpy(char* dest, char* src)
lw_strcpy:
	mov r8, rdi
	mov rdi, rsi 	; find the length of the source string
	call lw_strlen
	mov rdi, r8
	mov rdx, rax
	inc rdx 		; include the null
	call lw_memcpy
	ret

; char* lw_strncpy(char* dest, char* src, size_t count)
lw_strncpy:
	mov r8, rdi
	mov r9, rsi
	mov rdi, rsi
	mov rsi, rdx
	call lw_strnlen
	mov rdx, rax
	inc rdx			; for the null
	mov rdi, r8
	mov rsi, r9
	call lw_memcpy
	ret

; char* lw_strstr(char* string, char* needle)
lw_strstr:
	mov r8, rdi
	mov r9, rsi

	mov rdi, rsi		; get the length of the needle
	call lw_strnlen
	mov r11, rax		; stash the needle length

	mov al, byte [r9] ; get the first byte of needle
	mov rsi, rax
	mov rdi, r8

.continue:
	call lw_strchr		; find the next instance of the first byte
	cmp rax, 0x00
	jz .done		    ; no more instances of the token exist in our haystack
	mov rdi, rax
	mov r8, rax		    ; store our pointer to 'current'
	mov r10, rsi 	    ; stash the byte for later use
	mov rsi, r9
	mov rdx, r11
	call lw_strncmp
	cmp rax, 0x00	    ; were the strings equal?
	jz .found
	mov rsi, r10
	mov rdi, r8
	inc rdi
	jmp .continue

.found:
	mov rax, r8		   ; get back to the base of the string we just compared against
.done:
	ret
