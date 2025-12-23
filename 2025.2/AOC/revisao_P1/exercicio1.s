.data
.text 
.globl _start

_start:
	li x5, 3
	li x6, 2
	li x7, 5

	addi x7, x7, -5
	add x5, x6, x7

