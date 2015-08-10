#!/bin/bash

nasm -f elf64 strlib.S
nasm -f elf64 syscalls.S
nasm -f elf64 utils.S
gcc -nostdlib main.c lwclib.c -o $1 strlib.o syscalls.o utils.o
./$1
