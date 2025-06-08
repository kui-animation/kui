%define FILE_NUM 0644o
%define CREAT_F 64
%define WRITE_F 1
%define READ_F 0
%define LINE_LEN 6
%define H_RES 16
%define W_RES 32
%define RES 544

%define SYS_SLEEP 35
%define SYS_WRITE 1
%define SYS_READ 0
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_RMFILE 87
%define SYS_EXIT 60
%define STDIN 0
%define STDOUT 1


section .data
    mov_cur db 0x1b, "[1A"
    sleep_time dq 0, 250000000

section .bss
    file_prt resb 8
    mes resb LINE_LEN
    new_file resb 2
    buf resb RES+1
    file resb 16

section .text
global _start

_start:

    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, new_file
    mov rdx, 2
    syscall

    cmp byte[new_file], 'y'
    je get_file_name

    mov byte[file], 0x41
    mov byte[file+1], 0x0

                            ; open a file
    mov rax, SYS_OPEN
    mov rdi, file
    mov rsi, WRITE_F | CREAT_F         ; creat now file in write mode
    mov rdx, FILE_NUM
    syscall
    mov [file_prt], rax     ; set file pointer to the fd

loop:

                            ; read input in mes
    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, mes
    mov rdx, LINE_LEN
    syscall

    cmp rax, LINE_LEN
    jl start_exe

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


get_file_name:
    mov rax, SYS_READ
    mov rdi, STDIN
    mov rsi, file
    mov rdx, 16
    syscall
    
    mov byte[file+rax-1], 0x0
    jmp open_file

start_exe:
                            ; close file
    mov rax, SYS_CLOSE
    mov rdi, [file_prt]
    syscall 
    
open_file:
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
    mov rsi, mes
    mov rdx, LINE_LEN
    syscall

                            ; if end off file go to end_program
    cmp rax, LINE_LEN
    jl end_program

    cmp byte[mes], 'v'
    jne .next_str1
    cmp byte[mes+1], 'o'
    je voxel

.next_str1:
    cmp byte[mes], 's'
    jne .next_str2
    cmp byte[mes+1], 'b'
    jne .next_str2
    cmp byte[mes+2], 'u'
    jne .next_str2
    cmp byte[mes+3], 'f'
    je sbuf

.next_str2:


    cmp byte[mes], 's'
    jne .next_str3
    cmp byte[mes+1], 'l'
    jne .next_str3
    cmp byte[mes+2], 'e'
    jne .next_str3
    cmp byte[mes+3], 'e'
    jne .next_str3
    cmp byte[mes+4], 'p'
    je sleep

.next_str3:
    cmp byte[mes], 'p'
    jne .next_str4
    cmp byte[mes+1], 'r'
    jne .next_str4
    cmp byte[mes+2], 'i'
    jne .next_str4
    cmp byte[mes+3], 'n'
    jne .next_str4
    cmp byte[mes+4], 't'
    je print

.next_str4:
    jmp exe_program

print:
    
                            ; write char to the terminal
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, buf
    mov rdx, RES
    syscall

    call mov_up

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

sbuf:
    mov al, byte[mes+4]
    mov rbx, 0
.loop1:
    
    mov byte[buf+rbx], al

    inc rbx
    cmp rbx, RES
    jne .loop1

    call fix_buf

    jmp exe_program

voxel:

    movzx eax, byte[mes+3]
    movzx ebx, byte[mes+2]

    sub eax, 65
    sub ebx, 64

    imul ecx, eax, W_RES
    add ecx, ebx

    mov al, byte[mes+4]
    mov byte[buf+ecx], al

    jmp exe_program

sleep:

    mov rax, SYS_SLEEP
    mov rdi, sleep_time
    mov rsi, 0
    syscall

    jmp exe_program

fix_buf:
    mov rbx, 0

.loop1:
    mov rax, rbx
    imul rax, W_RES
    mov byte[buf+rax], 0xA

    inc rbx
    cmp rbx, H_RES+1
    jne .loop1

    mov byte[buf+RES], 0x0
    ret

mov_up:
    mov rbx, 0
.loop1:
    mov rax, SYS_WRITE
    mov rdi, STDOUT
    mov rsi, mov_cur
    mov rdx, 4
    syscall

    inc rbx
    cmp rbx, H_RES+1
    jne .loop1

    ret
