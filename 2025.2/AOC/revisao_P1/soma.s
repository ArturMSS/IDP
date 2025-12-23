.data
    .text
    .global _start

_start:
    j main

main:
    li a0, 5        # parâmetro: queremos soma(5)
    jal ra, soma    # chama a função recursiva

    li a7, 1        # syscall: print int
    ecall

    li a7, 10       # syscall: exit
    ecall

soma:
    addi sp, sp, -8     # reserva espaço na pilha
    sw ra, 4(sp)        # salva endereço de retorno
    sw a0, 0(sp)        # salva parâmetro original


    ble a0, x0, base     # caso base: se n <= 0, vai pra base

    addi a0, a0, -1     # prepara n - 1
    jal ra, soma        # chamada recursiva

    lw t0, 0(sp)        # recupera n original
    add a0, a0, t0      # soma resultado + n original
    j fim

base:
    li a0, 0            # soma(0) = 0

fim:
    lw ra, 4(sp)        # restaura endereço de retorno
    addi sp, sp, 8      # libera espaço da pilha
    jr ra               # retorna
