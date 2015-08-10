#pragma once
/*
The MIT License (MIT)

Copyright (c) 2015 Aaron Bray

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// this is the "operational" build.
// the lw_ prefix allows linking with regular libc,
// if desired for some reason (e.g., unit testing)
#ifndef _USING_LIB_STD
// string.h sub
#define memcpy(s, d, sz)			lw_memcpy(s, d, sz)
#define memset(d, v, sz)			lw_memset(d, v, sz)
#define memmove(d, s, sz)			lw_memmove(d, s, sz)
#define strlen(c)					lw_strlen(c)
#define strnlen(c, sz)				lw_strnlen(c, sz)
#define strchr(hs, ndl)				lw_strchr(hs, ndl)
#define memcmp(d, s, sz)			lw_memcmp(d, s, sz)
#define memchr(h, n, sz)			lw_memchr(h, n, sz)
#define strcmp(s1, s2)				lw_strcmp(s1, s2)
#define strncmp(s1, s2, sz)			lw_strncmp(s1, s2, sz)
#define strcpy(d, s)				lw_strcpy(d, s)
#define strncpy(d, s, sz)			lw_strncpy(d, s, sz)
#define strstr(hs, nd)				lw_strstr(hs, nd)

// syscall wrappers
#define open(fnm, flgs, md)			lw_open(fnm, flgs, md)
#define close(fd)					lw_close(fd)
#define read(fd, bf, sz)			lw_read(fd, bf, sz)
#define write(fd, bf, sz)			lw_write(fd, bf, sz)
#define lseek(fd, ofs, wh)			lw_lseek(fd, ofs, wh)
#define mmap(a, l, p, fl, fd, o) 	lw_mmap(a, l, p, fl, fd, o)
#define mprotect(st, sz, pr)		lw_mprotect(st, sz, pr)
#define munmap(ad, sz)				lw_munmap(ad, sz)
#define brk(b)						lw_brk(b)
#endif

// will need to be fixed for other
// platform sizes long term.
#define size_t 		unsigned long
#define ssize_t 	long

// strlib
extern size_t lw_strlen(char*);
extern size_t lw_strnlen(char*, size_t);
extern void* lw_memcpy(void*, void*, size_t);
extern void* lw_memmove(void*, void*, size_t);
extern void* lw_memset(void*, int, size_t);
extern char* lw_strchr(char* haystack, char needle);
extern int lw_memcmp(void* dest, void* src, size_t count);
extern void* lw_memchr(void* haystack, unsigned char needle, size_t count);
extern int lw_strcmp(char* s1, char* s2);
extern int lw_strncmp(char* s1, char* s2, size_t count);
extern char* lw_strcpy(char* dest, char* src);
extern char* lw_strncpy(char* dest, char* src, size_t count);
extern char* lw_strstr(char* haystack, char* needle);

// syscalls
extern int lw_close(unsigned int fd);
extern unsigned int lw_open(const char* fname, int flags, int mode);
extern ssize_t lw_read(unsigned int fd, char* buf, size_t count);
extern ssize_t lw_write(unsigned int fd, const char* buf, size_t count);
extern ssize_t lw_lseek(int fd, ssize_t offset, int whence);
extern void* lw_mmap(unsigned long addr, unsigned long len, unsigned long prot, 
	 	    		 unsigned long flags, unsigned long fd, unsigned long offset);
extern int lw_mprotect(unsigned long start, size_t len, unsigned long prot);
extern int lw_munmap(unsigned long addr, size_t len);
extern void* lw_brk(unsigned long brk);
// utils


// open flags
#define O_RDONLY	0x0000
#define O_WRONLY	0x0001
#define O_RDWR		0x0002
#define O_NONBLOCK	04000
#define O_APPEND	02000
#define O_TRUNC		01000
#define O_CREAT		0100
#define O_EXCL		0200
#define O_NOCTTY	0400
#define O_SYNC		010000
#define O_ASYNC		020000

// open mode
#define S_IRWXU		0000700
#define S_IRUSR		0000400
#define S_IWUSR		0000200
#define S_IXUSR		0000100
#define S_IRWXG		0000070
#define S_IRGRP		0000040
#define S_IWGRP		0000020
#define S_IXGRP		0000010
#define S_IRWXO		0000007
#define S_IROTH 	0000004
#define S_IWROTH 	0000002
#define S_IXROTH 	0000001
#define S_ISUID		0004000
#define S_ISGID		0002000
#define S_ISVTX		0001000

// not quite finished yet
int find_libc(void* out, size_t count);