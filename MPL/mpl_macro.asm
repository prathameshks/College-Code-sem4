; macro for printing
%macro print 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

; macro for reading from user
%macro read 2
    mov rax, 0
    mov rdi, 0
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

; macro for opening file
%macro open 2
    mov rax, 2
    mov rdi, %1
    mov rsi, %2
    mov rdx, 0
    syscall
%endmacro

; macro for reading from file
%macro readf 3
    mov rax, 0
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    syscall
%endmacro

; macro for writing to file
%macro write 3
    mov rax, 1
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    syscall
%endmacro

; macro for closing file
%macro close 1
    mov rax, 3
    mov rdi, %1
    syscall
%endmacro

; macro for creating file
%macro create 2
    mov rax, 85
    mov rdi, %1
    mov rsi, %2
    mov rdx, 0
    syscall
%endmacro

; macro for deleting file
%macro delete 1
    mov rax, 87
    mov rdi, %1
    syscall
%endmacro

; macro for exiting 
%macro exit 0
    mov rax, 60
    mov rdi, 0
    syscall
%endmacro



section .data

msg1 db 9,"India is best",10

msg1l equ $-msg1

%macro universal 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro


section .bss

section .txt
global _start:
_start:

universal 1,1,msg1,msg1l
universal 1,1,msg1,msg1l
universal 1,1,msg1,msg1l


mov rax,60
syscall
