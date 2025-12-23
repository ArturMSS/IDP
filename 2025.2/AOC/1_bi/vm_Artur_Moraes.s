.data
.align 2

#========== BYTECODES ===========#
# ---------------------------
# Programa 1 — sem saltos
# Faz: 10 20 ADD -> imprime 30
#      7 3 SUB -> imprime 4
# then HALT
# ---------------------------

bytecode_noflow:
    # instr 0: PUSH 10
    .word 1, 10
    # instr 1: PUSH 20
    .word 1, 20
    # instr 2: ADD
    .word 2, 0
    # instr 3: PRINT  (imprime 30)
    .word 4, 0

    # instr 4: PUSH 7
    .word 1, 7
    # instr 5: PUSH 3
    .word 1, 3
    # instr 6: SUB   (7 - 3 = 4)
    .word 3, 0
    # instr 7: PRINT (imprime 4)
    .word 4, 0
    # instr 8: HALT
    .word 6, 0

# ---------------------------
# Programa 2 — laço usando JZ (loop)
# Exemplo: imprime 42 repetidamente em loop infinito.
# Implementação do laço: PUSH 42 ; PRINT ; PUSH 0 ; JZ -3  -> volta ao instr 0
# Observação: usamos PUSH 0 + JZ -3 como "jump incondicional" (PUSH 0 garante JZ sempre salta).
# ---------------------------
bytecode_loop:
    # instr 0: PUSH 42
    .word 1, 42
    # instr 1: PRINT
    .word 4, 0
    # instr 2: PUSH 0        # prepara JZ para ser incondicional
    .word 1, 0
    # instr 3: JZ -3         # if (popped == 0) pc = pc + (-3) => volta a instr 1
    .word 5, -3
    # instr 4: HALT          # nunca alcançado neste exemplo (apenas por segurança)
    .word 6, 0
# ---------------------------
# Programa 3 — Teste de números negativos
# Testa: positivos, negativos, zero, e operações mistas
# ---------------------------
bytecode_negative_test:
    # Teste 1: Número positivo simples
    # instr 0: PUSH 42
    .word 1, 42
    # instr 1: PRINT  (imprime 42)
    .word 4, 0
    
    # Teste 2: Zero
    # instr 2: PUSH 0
    .word 1, 0
    # instr 3: PRINT  (imprime 0)
    .word 4, 0
    
    # Teste 3: Número negativo direto
    # instr 4: PUSH -15
    .word 1, -15
    # instr 5: PRINT  (imprime -15)
    .word 4, 0
    
    # Teste 4: Subtração que resulta em negativo
    # instr 6: PUSH 5
    .word 1, 5
    # instr 7: PUSH 10
    .word 1, 10
    # instr 8: SUB  (5 - 10 = -5)
    .word 3, 0
    # instr 9: PRINT  (imprime -5)
    .word 4, 0
    
    # Teste 5: Adição com negativo
    # instr 10: PUSH -20
    .word 1, -20
    # instr 11: PUSH 15
    .word 1, 15
    # instr 12: ADD  (-20 + 15 = -5)
    .word 2, 0
    # instr 13: PRINT  (imprime -5)
    .word 4, 0
    
    # Teste 6: Dois negativos
    # instr 14: PUSH -8
    .word 1, -8
    # instr 15: PUSH -3
    .word 1, -3
    # instr 16: ADD  (-8 + -3 = -11)
    .word 2, 0
    # instr 17: PRINT  (imprime -11)
    .word 4, 0
    
    # Teste 7: Subtração de negativos
    # instr 18: PUSH -10
    .word 1, -10
    # instr 19: PUSH -5
    .word 1, -5
    # instr 20: SUB  (-10 - (-5) = -10 + 5 = -5)
    .word 3, 0
    # instr 21: PRINT  (imprime -5)
    .word 4, 0
    
    # instr 22: HALT
    .word 6, 0

#teste de soma
bytecode_soma:
    .word 1, 10 # PUSH 10
    .word 1, 2  # PUSH 2
    .word 3, 0  # SUB
    .word 1, 5  # PUSH 5
    .word 2, 0  # ADD
    .word 4, 0  # PRINT
    .word 6, 0  # HALT

#buffer pra conversao de int pra string
buffer: 
	.zero 32
buffer_end:

newline: 
	.asciz "\r\n"

stack_vm:
	.zero 1024
stack_vm_end:
# =============== COMEÇO DAS FUNÇÕES ================== #
.text
.globl _start

convert_int_str:
	la t0, buffer_end      # t0 aponta para o fim do buffer
	li t1, 0
	sb t1, 0(t0)           # Coloca '\0' no final
	
	# Verificar negativo
	li t4, 0
	bgez a0, loop_div      # Se >= 0 continua normal

	li t4, 1               # flag = negativo
	neg a0, a0             # a0 = -a0
loop_div: 
	li t1, 10              # Para fazer as divisões
	div t2, a0, t1         # t2 = a0/10
	rem t3, a0, t1         # t3 = a0% 10(ultimo digito)
	addi t3, t3, 48        # ascii
	addi t0, t0, -1        # Move ponteiro para tras
	sb t3, 0(t0)           # Escreve digito na posicao anterior
	mv a0, t2              # a0 = parte restante
	bnez a0, loop_div 
	
	# Se nao for negativo pula a adicao do '-'
	beqz t4, skip_minus

	# Adiciona '-' se era negativo
	addi t0, t0, -1        # move ponteiro para tras
	li t1, 45              # ASCII '-' 
	sb t1, 0(t0)           # Save byte

skip_minus:
	la t1, buffer_end
	sub a2, t1, t0         # tamanho da string
	mv a1, t0              # Ponteiro para string
	ret

#============================ COMEÇO DO CODIGO PRINCIPAL ===========================#
# REGISTRADORES 
# s0 = PC (Program Counter)
# s1 = Base do bytecode
# s2 = SP (Stack Pointer)
# s3 = Stack limit 
_start:
	la s2, stack_vm_end    # SP = Fim da pilha
	la s3, stack_vm        # Limite inferior
	li s0, 0               # Inicializando o indice de instruções com 0 | PC = 0
	la s1, bytecode_negative_test # Carregando as instruções | escoler loop ou flow 

vm_loop: 
	slli t0, s0, 3         # t0 = pc(program counter)*8
	add t0, s1, t0         # t0 = base + (pc << 3)
	lw t1, 0(t0)           # opcode = primeiro word
	lw t2, 4(t0)           # operand = segundo word

	li t3, 1               # Para funcionar o beq
	beq t1, t3, op_push
	li t3, 2
	beq t1, t3, op_add
	li t3, 3
	beq t1, t3, op_sub
	li t3, 4
	beq t1, t3, op_print
	li t3, 5
	beq t1, t3, op_jz
	li t3, 6
	beq t1, t3, vm_exit

	jal x0, vm_exit        # Opcode invalido

op_push:
        # Overflow
	addi t4, s2, -4        # Salva o endereço abaixo em t4 para checar overflow
	la t5, stack_vm
	blt t4, t5, vm_exit    # Overflow check

	addi s2, s2, -4        # SP = SP -4 | desce o endereço
	sw t2, 0(s2)           # Salva operand no topo | faz o push na memoria
	addi s0, s0, 1         # PC += 1
	jal x0, vm_loop        # Volta ao loop

op_add: 
	# Underflow check
	la t5, stack_vm_end 
	beq s2, t5, vm_exit

	# Salvar e dar pop no primeiro valor
	lw t3, 0(s2)           # Salva o valor do topo em t3
	addi s2, s2, 4         # Remove topo
	
	# Underflow check
	la t5, stack_vm_end
	beq s2, t5, vm_exit

	# Salvar e dar pop no segundo valor
	lw t4, 0(s2)          # Salva em t4 
	addi s2, s2, 4        # Sobe mais uma posição na pilha (pop)

	# Overflow check
	addi t6, s2, -4       # Novo SP = s2 - 4
	la t5, stack_vm 
	blt t6, t5, vm_exit   # Overflow ao tentar dar push
	
	# Soma e push resultado
	add t4, t4, t3        # Soma t3 e t4 e salva em t4
	addi s2, s2, -4       # Avança o topo da pilha
	sw t4, 0(s2)          # Salva o valor da soma no topo da pilha
	
	# Ajustando PC e voltando ao loop
	addi s0, s0, 1        # PC += 1
	jal x0, vm_loop       # Volta ao loop

op_sub: 
	# Underflow check
	la t5, stack_vm_end
	beq s2, t5, vm_exit

	# Salvar e  pop primeiro valor
	lw t3, 0(s2)         # Salva o valor do topo em t3
	addi s2, s2, 4       # pop
	
	# Underflow check
	la t5, stack_vm_end
	beq s2, t5, vm_exit

	# Salva e pop segundo valor
	lw t4, 0(s2)        # Salva em t4
	addi s2, s2, 4      # Volta mais uma posição na pilha (pop)
	
	# Overflow check
	addi t6, s2, -4     # Novo SP = s2 - 4
	la t5, stack_vm 
	blt t6, t5, vm_exit # Overflow ao tentar dar push

	# sub e push
	addi s2, s2, -4     # Desce SP
	sub t4, t4, t3      # Subtrai t3( valor do topo) do t4 (penultimo valor)
	sw t4, 0(s2)        # Salva o valor da subtração no topo da pilha

	# Ajustando PC e voltando ao loop
	addi s0, s0, 1      # PC += 1
	jal x0, vm_loop     # Volta ao loop

op_print: 
	# Underflow check
	la t5, stack_vm_end
	beq s2, t5, vm_exit
	
	# Salva e pop
	lw t3, 0(s2)       # Salva o valor do topo em t3
	addi s2, s2, 4     # pop

	# Converte pra string
	mv a0, t3          # Coloca o valor em a0
	call convert_int_str

	li a7, 64          # Syscall write
	li a0, 1           # fd = stdout
	ecall 
	
	# Print newline
	li a7, 64         # Syscall write
	li a0, 1          # stdout
	la a1, newline    # Escreve \n
	li a2, 2
	ecall 

	# Ajustando PC e voltando ao loop
	addi s0, s0, 1    # PC += 1
	jal x0, vm_loop   # Volta ao loop

op_jz: 
	# Underflow check
	la t5, stack_vm_end
	beq s2, t5, vm_exit

	# Salvando valor dando pop e checando se faz salto
	lw t3, 0(s2)      # t3 = topo
	addi s2, s2, 4    # pop apos salvar valor
	bnez t3, jz_skip  # Se o topo n for 0 ja volta pro while
	
	# Salta e volta ao loop
	add s0, s0, t2    # pc = pc + i
	j vm_loop

jz_skip:
	addi s0, s0, 1    # PC += 1
	jal x0, vm_loop   # Volta ao loop

vm_exit: 
	li a7, 93         # Syscall exit
	li a0, 0          # Exit code
	ecall
