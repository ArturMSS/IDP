.data
    .text
    .global _start

_start:
    j main

main:
    li a0, 10        # n (altere aqui)
    jal ra, fib      # chama fib(n)
    li a7, 1         # print int
    ecall
    li a7, 10        # exit
    ecall

# fib(n): a0 = n, retorna a0 = F(n)
fib:
    addi sp, sp, -12     # frame: 12 bytes
    sw   ra, 8(sp)       # salva ra
    sw   s0, 4(sp)       # salva s0 (callee-saved)
    sw   a0, 0(sp)       # salva n

    ble  a0, 1, base     # se n <= 1, caso base (retorna n)

    addi a0, a0, -1
    jal  ra, fib         # F(n-1)
    mv   s0, a0          # s0 = F(n-1)

    lw   a0, 0(sp)       # a0 = n original
    addi a0, a0, -2
    jal  ra, fib         # F(n-2)

    add  a0, a0, s0      # a0 = F(n-2) + F(n-1)
    j    fim

base:
    # a0 já é 0 ou 1 — só seguir pro retorno

fim:
    lw   s0, 4(sp)       # restaura s0
    lw   ra, 8(sp)       # restaura ra
    addi sp, sp, 12      # fecha frame
    jr   ra
