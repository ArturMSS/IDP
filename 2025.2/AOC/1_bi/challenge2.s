.data
src:
    .byte 1, 2, 3, 4
	
len: .word 4
	
dest:
	.byte 0, 0, 0, 0 #salvando bytes vazios

	.text
	.globl _start
_start:
	la t0, src 
	la t1, len
	lw t1, 0(t1)
    la t2, dest
    
	jal x0, loop
loop:
	beq t1, x0, done
	lbu t5, 0(t0) #load byte do src
    sb t5, 0(t2) #save byte no dest
    addi t1, t1, -1
    addi t0, t0, 1 #avança ponteiro src
    addi t2, t2, 1 #avança ponteiro  dest
      
    jal x0, loop

done:
    li a0, 0

