%define FILE_NUM 0644o
%define CREAT_F 64
%define WRITE_F 1
%define READ_F 0


%define SYS_WRITE 1
%define SYS_READ 0
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_RMFILE 87
%define SYS_EXIT 60
%define STDIN 0
%define STDOUT 1



section .data
file db "a", 0x0            ; set file to tmp file

section .bss
    file_prt resb 8         ; reserve 64 bits for the file pointer
    mes resb 32             ; reserve 32 byte for the mesige
    char resb 1             ; reserve 1 byte for the char

section .text
global _start

_start:

                            ; open a file
    mov rax, SYS_OPEN
    mov rdi, file
    mov rsi, WRITE_F | CREAT_F         ; creat now file in write mode
    mov rdx, FILE_NUM
    syscall
    mov [file_prt], rax     ; set file pointer to the fd

    ;---------------;
    ; print to file ;
    ;---------------;

loop:

                            ; read input in mes
    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, mes
    mov rdx, 32
    syscall

                            ; comper if mes is end
    cmp byte[mes], 'e'
    jne print_loop
    cmp byte[mes+1], 'n'
    jne print_loop
    cmp byte[mes+2], 'd'
    jne print_loop
    cmp byte[mes+3], 0xA
    je start_exe            ; if is end go start_exe

print_loop:
   
                            ; write to the tmp file 
    mov rdi, [file_prt]
    mov rdx, rax
    mov rax, SYS_WRITE
    mov rsi, mes
    syscall

    jmp loop                ; go to start of loop

start_exe:
                            ; close file
    mov rax, SYS_CLOSE
    mov rdi, [file_prt]
    syscall
    
                            ; open it in read mode
    mov rax, SYS_OPEN
    mov rdi, file
    mov rsi, READ_F
    mov rdx, FILE_NUM
    syscall

    mov [file_prt], rax     ; set file pointer to fd

exe_program:
                            ; read char in file
    mov rax, SYS_READ
    mov rdi, [file_prt]
    mov rsi, char
    mov rdx, 1
    syscall

                            ; if end off file go to end_program
    cmp rax, 0
    je end_program

                            ; write char to the terminal
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, char
    mov rdx, 1
    syscall

    jmp exe_program         ; go to exe_program


end_program:

                            ; close file
    mov rax, SYS_CLOSE
    mov rdi, [file_prt]
    syscall

                            ; remove file
    mov rax, SYS_RMFILE
    mov rdi, file
    syscall
    
                            ; end program 
    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

