section .data
section .text
bits 64
default rel

global asmdaxpy

asmdaxpy:
push rbp
mov rbp, rsp
add rbp, 16

; ecx first element
; xmm1 second element
; r8 third element
; r9 fourth element
; rbp + 32 fifth element

mov r10, [rbp + 32]

xor rax, rax

compute:
cmp eax, ecx
jge done

movsd xmm0, [r8 + rax * 8]
mulsd xmm0, xmm1
addsd xmm0, [r9 + rax * 8]
movsd [r10 + rax * 8], xmm0

inc eax
jmp compute


done:
pop rbp

ret
