.section .data
fmt_in:
    .string "%d %d %d"
fmt_err:
    .string "Entradas invalidas.\n"
fmt_notprime:
    .string "O modulo nao eh primo.\n"
fmt_out:
    .string "A exponencial modular %d elevado a %d (mod %d) eh %d\n"

.section .bss
    .lcomm N1, 4
    .lcomm N2, 4
    .lcomm N3, 4

.section .text

.globl ehprimo
.type ehprimo, @function
ehprimo:
    push    %rbp
    mov     %rsp, %rbp
    mov     %edi, %eax         # eax = n
    cmp     $1, %edi
    je      .Lfalse
    mov     $2, %ecx           # i = 2
.Ltest:
    mov     %ecx, %edx
    imul    %ecx, %edx         # edx = i * i
    cmp     %edi, %edx
    jg      .Ldone             # if i*i > n, prime
    mov     %edi, %eax         # prepare dividend n
    cdq                        # sign-extend for idiv
    idiv    %ecx               # divide by i, remainder in edx
    test    %edx, %edx         # check remainder
    je      .Lfalse            # if n % i == 0, not prime
    inc     %ecx               # i++
    jmp     .Ltest
.Lfalse:
    mov     $0, %eax           # return false
    pop     %rbp
    ret
.Ldone:
    mov     $1, %eax           # return true
    pop     %rbp
    ret

.globl mod_exp
.type mod_exp, @function
mod_exp:
    push    %rbp
    mov     %rsp, %rbp
    # args: base in edi, expo in esi, mod in edx
    mov     %edx, %r9d        # save mod in r9d
    mov     $1, %r8d          # result = 1
    # base %= mod
    mov     %edi, %eax
    cdq
    idiv    %r9d              # divide by mod, remainder in edx
    mov     %edx, %edi        # edi = base % mod
.Lexp_loop:
    test    $1, %esi
    jz      .Lskip_mul
    # result = (result * base) % mod
    mov     %r8d, %eax
    imul    %edi, %eax
    cdq
    idiv    %r9d              # divide by mod, remainder in edx
    mov     %edx, %r8d        # result = remainder
.Lskip_mul:
    # base = (base * base) % mod
    mov     %edi, %eax
    imul    %edi, %eax
    cdq
    idiv    %r9d              # divide by mod, remainder in edx
    mov     %edx, %edi        # base = remainder
    shr     $1, %esi          # expo >>= 1
    jnz     .Lexp_loop
    mov     %r8d, %eax        # return result
    pop     %rbp
    ret

.globl main
.type main, @function
main:
    push    %rbp
    mov     %rsp, %rbp
    sub     $16, %rsp
    # read inputs: scanf("%d %d %d", &N1, &N2, &N3)
    lea     fmt_in(%rip), %rdi
    lea     N1(%rip), %rsi
    lea     N2(%rip), %rdx
    lea     N3(%rip), %rcx
    xor     %eax, %eax         # clear AL for variadic call
    call    scanf

    # validate 1 <= Ni <= 65535
    mov     N1(%rip), %eax
    cmp     $1, %eax
    jl      .err_input
    cmp     $65535, %eax
    jg      .err_input
    mov     N2(%rip), %eax
    cmp     $1, %eax
    jl      .err_input
    cmp     $65535, %eax
    jg      .err_input
    mov     N3(%rip), %eax
    cmp     $1, %eax
    jl      .err_input
    cmp     $65535, %eax
    jg      .err_input

    # check prime(N3)
    mov     N3(%rip), %edi
    call    ehprimo
    test    %eax, %eax
    jne     .compute
    # not prime: print error
    lea     fmt_notprime(%rip), %rdi
    xor     %eax, %eax         # clear AL for variadic call
    call    printf
    jmp     .exit

.err_input:
    lea     fmt_err(%rip), %rdi
    xor     %eax, %eax         # clear AL for variadic call
    call    printf
    jmp     .exit

.compute:
    # result = mod_exp(N1, N2, N3)
    mov     N1(%rip), %edi
    mov     N2(%rip), %esi
    mov     N3(%rip), %edx
    call    mod_exp
    mov     %eax, %r8d         # save result

    # printf output
    lea     fmt_out(%rip), %rdi
    mov     N1(%rip), %rsi
    mov     N2(%rip), %rdx
    mov     N3(%rip), %rcx
    xor     %eax, %eax         # clear AL for variadic call
    call    printf

.exit:
    mov     $0, %eax
    leave
    ret

.section .note.GNU-stack,"",@progbits
