.data

.text
.globl _start
# B[8] = A[i] + A[j]
# i está em x28
# j está em x29
# Base de A está em x10
# Base de B está em x11
# Usando 4 bytes por elemento (32 bits)

_start:
    # Calcular endereço de A[i]
    slli x30, x28, 2      # x30 = i * 4
    add  x30, x30, x10    # x30 = &A[i]
    
    # Calcular endereço de A[j]
    slli x31, x29, 2      # x31 = j * 4
    add  x31, x31, x10    # x31 = &A[j]
    
    # Carregar valores
    lw   x5, 0(x30)       # x5 = A[i] (carrega em f)
    lw   x6, 0(x31)       # x6 = A[j] (carrega em g)
    
    # Somar os valores
    add  x7, x5, x6       # x7 = A[i] + A[j] (resultado em h)
    
    # Armazenar em B[8]
    sw   x7, 32(x11)      # B[8] = A[i] + A[j] (offset = 8*4 = 32)
