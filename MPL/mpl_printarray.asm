;macro to display messages
%macro print 2
mov rax,1
mov rdi,1
mov rsi,%1
mov rdx,%2
syscall
%endmacro

; macro for array input output 
%macro universal 4
mov rax,%1
mov rdi,%2
mov rsi,%3
add rsi,rbx
mov rdx,%4
syscall
%endmacro


section .data
m1 db "Please enter 5 numbers of 64 bit(16 digits)",10
m1l equ $-m1

m2 db "Entered Numbers are :",10
m2l equ $-m2

count db 05

section .bss
array resq 6

section .text
global _start
_start:

mov rbx,00
print m1,m1l

;logic to accept 5 numbers
input:
universal 0,0,array,17
; mov rax,00
; mov rdi,00
; mov rsi,array
; add rsi,rbx
; mov rdx,17
; syscall

add rbx,17
dec byte[count]
jnz input


;display logic
print m2,m2l

mov byte[count],05
mov rbx,00

display:
universal 1,1,array,17

; mov rax,01
; mov rdi,01
; mov rsi,array
; add rsi,rbx
; mov rdx,17
; syscall

add rbx,17
dec byte[count]
jnz display


exit:
mov rax,60
mov rdi,00
syscall


; nasm -f elf64 mpl_printarray.asm;ld -o a mpl_printarray.o;./a
; 1567812345123678
; 2212345345678678
; 3267812345345678
; 4456781234567812
; 5123456781234567