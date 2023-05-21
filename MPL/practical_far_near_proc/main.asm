
extern far_proc

global filename,file_hand,buf,abuf_len

%include "macro.asm"

section .data
    msg db "Program To Count Spaces,Newlines and Characters from file",10
    msg_len equ $-msg 

    msg_fname db "Enter File Name : "
    msg_fname_len equ $-msg_fname

    msg_err db "File Not Found",10
    msg_err_len equ $-msg_err


    msg_exit db "Exiting From Program",10
    msg_exit_len equ $-msg_exit


    msg_char db "Enter Character To Count : "
    msg_char_len equ $-msg_char

    new_line db 10
    space db " "


section .bss
    buf resb 4096
    buf_len equ $-buf
    
    filename resb 50
    char resb 2

    file_hand resq 1
    abuf_len resq 1

section .text
    global _start
    _start:

    print msg,msg_len
    print new_line,1
    print new_line,1

    print msg_fname,msg_fname_len
    read filename,50
    dec rax
    mov [filename+rax],0

    print msg_char,msg_char_len
    read char,2
    dec rax
    mov [filename+rax],0
    
    fopen filename
    cmp rax,-1h
    jle error
    mov [file_hand],rax

    fread file_hand,buf,buf_len
    mov [abuf_len],rax

    call far_proc
    jmp Exit

error:
print msg_err,msg_err_len


Exit:
    print msg_exit,msg_exit_len
    exit


