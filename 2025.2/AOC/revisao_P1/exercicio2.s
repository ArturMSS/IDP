.data

.text 
.globl _start
# 2.3 [5] <§§2.2, 2.3> For the following C statement, write the
# corresponding RISC-V assembly code. Assume that the variables
# f, g, h, i, and j are assigned to registers x5, x6, x7, x28, and x29,
# respectively. Assume that the base address of the arrays A and B
# are in registers x10 and x11, respectively.
# B[8] = A[i−j];
_start:
    sub x30, x28, x29  # x30 = i - j
    slli x30, x30, 2 # x30 = (i-j) * 4
    add x30, x10, x30 # x30 = base adress of A + offset
    lw x31, 0(x30) # x31 = A[i - j]
    sw x31, 32(x11) # B[8] = x31
    
