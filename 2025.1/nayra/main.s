.data
# Mensagens (cada string termina com byte zero)
str_err:
    .ascii "Entradas invalidas.\n"
    .byte 0
str_notprime:
    .ascii "O modulo nao eh primo.\n"
    .byte 0

str1:
    .ascii "A exponencial modular "
    .byte 0
str2:
    .ascii " elevado a "
    .byte 0
str3:
    .ascii " (mod "
    .byte 0
str4:
    .ascii ") eh "
    .byte 0
str5:
    .ascii ".\n"
    .byte 0

# Espaço para os três inteiros
N1:
    .word 0
N2:
    .word 0
N3:
    .word 0

    .text
    .globl main
main:
    #--- Leitura de N1
    li   a7, 5
    ecall
    la   t0, N1
    sw   a0, 0(t0)

    #--- Leitura de N2
    li   a7, 5
    ecall
    la   t0, N2
    sw   a0, 0(t0)

    #--- Leitura de N3
    li   a7, 5
    ecall
    la   t0, N3
    sw   a0, 0(t0)

    #--- Validação 1 ≤ Ni ≤ 65535
    li   t1, 1
    li   t2, 65535

    la   t0, N1
    lw   t3, 0(t0)
    blt  t3, t1, error_input
    bgt  t3, t2, error_input

    la   t0, N2
    lw   t3, 0(t0)
    blt  t3, t1, error_input
    bgt  t3, t2, error_input

    la   t0, N3
    lw   t3, 0(t0)
    blt  t3, t1, error_input
    bgt  t3, t2, error_input

    #--- Teste de primalidade de N3 (em t3)
    li   t2, 2

prime_loop:
    mul  t4, t2, t2
    bgt  t4, t3, prime_done
    remu   t4, t3, t2
    beq  t4, zero, not_prime
    addi t2, t2, 1
    j    prime_loop

prime_done:
    #--- Exponenciação modular
    la   t0, N1
    lw   t0, 0(t0)
    la   t1, N2
    lw   t1, 0(t1)
    la   t2, N3
    lw   t2, 0(t2)
    remu  t0, t0, t2
    li   t3, 1

modexp_loop:
    andi  t4, t1, 1
    beq   t4, zero, skip_mul
    mul   t3, t3, t0
    remu  t3, t3, t2

skip_mul:
    mul  t0, t0, t0
    remu  t0, t0, t2
    srli t1, t1, 1
    bnez t1, modexp_loop

    #--- Impressão: str1
    li   a7, 4
    la   a0, str1
    ecall

    #--- N1
    la   t0, N1
    lw   a0, 0(t0)
    li   a7, 1
    ecall

    #--- str2
    li   a7, 4
    la   a0, str2
    ecall

    #--- N2
    la   t0, N2
    lw   a0, 0(t0)
    li   a7, 1
    ecall

    #--- str3
    li   a7, 4
    la   a0, str3
    ecall

    #--- N3
    la   t0, N3
    lw   a0, 0(t0)
    li   a7, 1
    ecall

    #--- str4
    li   a7, 4
    la   a0, str4
    ecall

    #--- resultado (t3)
    mv   a0, t3
    li   a7, 1
    ecall

    #--- str5
    li   a7, 4
    la   a0, str5
    ecall

    #--- Fim normal
    li   a7, 10
    ecall

not_prime:
    li   a7, 4
    la   a0, str_notprime
    ecall
    li   a7, 10
    ecall

error_input:
    li   a7, 4
    la   a0, str_err
    ecall
    li   a7, 10
    ecall