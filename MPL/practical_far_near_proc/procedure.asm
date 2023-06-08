
global far_proc

;externb filename,file_hand,buf,abuf_len
extern filename,file_hand,buf,abuf_len,char


%include "macro.asm"

section .data
    msg_char db "Character Count is : "
    msg_char_len equ $-msg_char

    msg_space db "Space Count is : "
    msg_space_len equ $-msg_space

    msg_nline db "New Line Count is : "
    msg_nline_len equ $-msg_nline

    new_line db 10
    space db " "


section .bss
    s_count resq 1
    n_count resq 1
    c_count resq 1


section .text
    global _main
    _main:

far_proc:

    mov rsi,0
    mov rcx,0

    mov bl,[char]
    mov rsi,buf
    mov rcx,[abuf_len]

    again:
    mov al,[rsi]

    s_next:
        cmp al,20h
        jne n_next
        inc qword[s_count]
        jmp next

    n_next:
        cmp al,10h
        jne c_next
        inc qword[n_count]
        jmp next


    c_next:
        cmp al,20h
        jne next
        inc qword[c_count]


    next:
        inc rsi
        dec rcx
        jnz again
    
    print msg_space,msg_space_len
ret
