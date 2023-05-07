%macro print 2
mov rax,1
mov rdi,1
mov rsi,%1
mov rdx,%2
syscall
%endmacro


section .data 

m_prt db "Processor is in protected mode",10
ml_prt equ $-m_prt

m_rel db "Processor is in Real mode",10
ml_rel equ $-m_rel

m_gdt db "Data in GDTR is",10
ml_gdt equ $-m_gdt

m_ldt db "Data in LDTR is",10
ml_ldt equ $-m_ldt

m_idt db "Data in IDTR is",10
ml_idt equ $-m_idt

m_tr db "Data in TR is",10
ml_tr equ $-m_tr

;m1 db "Sample:"
;m1l equ $-m1

space db " "
endl db 10
col db ":"


section .bss  
    gdt_data resd 1 
        resw 1 ;32+16 bits
    
    ldt_data resw 1 ;16 bits
    
    idt_data resd 1
        resw 1
        
    tr_data resw 1
    
    cr0_data resd 1
    
    dnum_buff resb 04 ;4 bytes = 32 bits


section .text
    global _start
    _start:
    
    smsw eax ;store cr0 data to eax register
    
    bt eax,0
    
    jnc disp_real
    print m_prt,ml_prt
    jmp next1
    
    disp_real:
    print m_rel,ml_rel
    next1:
    
    sgdt [gdt_data]
    sldt [ldt_data]
    sidt [idt_data]
    str [tr_data]
    
    print 
    
mov rax,60
mov rdi,0
syscall


;nasm -f elf64 mpl_7_displayRegs.asm;ld -o a mpl_7_displayRegs.o; ./a

