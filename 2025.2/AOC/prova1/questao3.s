.data
.align 2
.text
.globl main
#RESULTADO EM A0
main:
     li a0, 5 # numero a ser somado
    jal ra, loop
    
    li a7, 93 
    ecall
    
loop:
     addi sp, sp, -8 #espaço na stack
     sw ra, 4(sp) # endereço
     sw a0, 0(sp) # numero original
     
     beqz a0, zero # caso igual a zero
     addi a0, a0, -1 # novo a0 = a0(anterior) -1
     jal ra, loop
     lw t2, 0(sp) # n = 0(sp)
     add a0, a0, t2 # n + n-1
     jal x0, end
zero:
    addi a0, a0, 0
    
end: 
    lw ra, 4(sp) # volta endereço
    addi sp, sp, 8 # parecido com pop
    ret

