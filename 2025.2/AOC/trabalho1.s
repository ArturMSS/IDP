.text
.globl f

f:
loop:
lw t0, 0(a0)
beq t0, x0, end
add a1, a1, t0
addi a0, a0, 4
jal x0, loop

end:
addi a0, a1, 0
jalr x0, 0(ra)


