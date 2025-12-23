.data
result_msg: .string "Fatorial de 5 = "

.text
.globl main

main:
    # Salva o endereço de retorno
    addi sp, sp, -4
    sw ra, 0(sp)
    
    # Chama fatorial(5)
    li a0, 5
    jal ra, fatorial
    
    # Resultado está em a0
    # (Aqui você poderia imprimir o resultado)
    
    # Restaura o endereço de retorno
    lw ra, 0(sp)
    addi sp, sp, 4
    
    # Termina o programa
    li a7, 10
    ecall

# Função recursiva: fatorial(n)
# Entrada: a0 = n
# Saída: a0 = n!
fatorial:
    # Caso base: se n <= 1, retorna 1
    li t0, 1
    ble a0, t0, caso_base
    
    # Caso recursivo: n * fatorial(n-1)
    # Salva registradores na pilha
    addi sp, sp, -8
    sw ra, 4(sp)    # Salva endereço de retorno
    sw a0, 0(sp)    # Salva n
    
    # Calcula fatorial(n-1)
    addi a0, a0, -1  # n-1
    jal ra, fatorial # Chamada recursiva
    
    # Restaura n
    lw t1, 0(sp)
    
    # Multiplica n * fatorial(n-1)
    mul a0, t1, a0
    
    # Restaura registradores
    lw ra, 4(sp)
    addi sp, sp, 8
    
    ret

caso_base:
    li a0, 1
    ret
