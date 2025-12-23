.data
.align 2
array: 
    .word 1
    .word 2
    .word -3
    .word 4

.text
.globl main

main:
    li t1, 16 # tamanho do array (4 words = 16 bytes)
    li t2, 0 # new_size
    la s1, array # dados
loop:
    beqz t1 end
    lw t4, 0(s1) # numero do 1
    bgez t4, soma
    addi t1, t1, -4
    addi s1, s1, 4
    jal x0, loop
soma: 
    addi t2, t2, 4
    addi t1, t1, -4
    addi s1, s1, 4
    bnez t1, loop
end: 
    addi a1, t2, 0
    li a7, 93
    li a0, 0
    ecall

