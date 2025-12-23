.data
records:
#record 1
	.word 0 #id
	.half 10 #grade
	.byte 0x0 #flags
	.byte 0x0 #pad
	
	.word 1 #id
	.half 6 #grade
	.byte 0x0 #flags
	.byte 0x0 #pad

	.word 2 #id
	.half 5 #grade
	.byte 0x0
	.byte 0x0
	
count: 
	.word 3 #numero de registros

sum:
	.word 0 #ja salvando aq a soma

	.text
	.globl _start
_start:
	la t0, records 
	la t1, count
	lw t1, 0(t1)

	jal x0, loop
loop:
	beq t1, x0, done
	lb t5, 6(t0)
    addi t1, t1, -1
    lh t3, 4(t0)
    addi t0, t0, 8 #avança ponteiro
    bne t5, x0, loop
    add t2, t2, t3
    jal x0, loop

done:
    la t4, sum
    sw t2, 0(t4)

