%macro print 2
    mov rax,1
    mov rdi,1
    mov rsi,%1
    mov rdx,%2
    syscall
%endmacro

%macro universal 4
    mov rax,%1
    mov rdi,%2
    mov rsi,%3
    add rsi,rbx
    mov rdx,%4
    syscall
%endmacro

section .data
m1 db "ASM Program for Creating Array and Displaying it",10
m1l equ $-m1

m2 db "Enter a 64 bit Number:"
m2l equ $-m2

m3 db "Numbers Entered Are",10
m3l equ $-m3

section .bss
arr resq 6
count resb 1

section .text
global _start
_start:
    print m1,m1l

    mov byte[count],05
    mov rbx,00
    input_loop:
        print m2,m2l
        universal 0,0,arr,17
        add rbx,17
        dec byte[count]
        jnz input_loop

    ;display 
    print m3,m3l

    mov rbx,00
    mov byte[count],05
    display_loop:
        universal 1,1,arr,17
        add rbx,17
        dec byte[count]
        jnz display_loop

mov rax,60
mov rdi,0
syscall

;nasm -f elf64 mpl1_array.asm -o a.o ;ld a.o  -o a ;./a