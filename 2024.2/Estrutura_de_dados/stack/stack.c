#include <stdio.h>
#include <stdlib.h>

#define MAX 32  // Limite de dígitos para conversões (adequado para inteiros de 32 bits)
#define BASE_BINARIO 2
#define BASE_OCTAL 8
#define BASE_HEXADECIMAL 16

typedef struct Pilha {
    int topo;
    int elementos[MAX];
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *p, int valor) {
    if (p->topo < MAX - 1) {
        p->topo++;
        p->elementos[p->topo] = valor;
    } else {
        printf("Erro: Pilha cheia!\n");
    }
}

// Função para desempilhar um valor da pilha
int desempilhar(Pilha *p) {
    if (p->topo == -1) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    return p->elementos[p->topo--];
}

// Função para exibir a pilha (do topo para a base)
void exibirPilha(Pilha *p) {
    while (p->topo != -1) {
        printf("%d", desempilhar(p));
    }
    printf("\n");
}

// Função genérica para conversão de decimal para qualquer base
void conversaoDecimalParaBase(int numero, int base) {
    if (numero == 0) {  // Tratamento para o caso de número 0
        printf("Resultado: 0\n");
        return;
    }

    Pilha p;
    inicializarPilha(&p);
    char hexDigits[] = "0123456789ABCDEF";  // Usado para conversão para hexadecimal

    while (numero > 0) {
        empilhar(&p, numero % base);
        numero /= base;
    }

    // Exibição do resultado da conversão
    printf("Resultado: ");
    if (base == BASE_HEXADECIMAL) {
        // Para hexadecimal, mapeamos os valores para os caracteres '0-9', 'A-F'
        while (p.topo != -1) {
            printf("%c", hexDigits[desempilhar(&p)]);
        }
    } else {
        exibirPilha(&p);
    }
}

// Função para obter a entrada do usuário
int obterEntradaUsuario() {
    int numero;
    printf("Digite um numero inteiro em base decimal: ");
    while (scanf("%d", &numero) != 1) {
        printf("Entrada inválida. Tente novamente: ");
        while(getchar() != '\n');  // Limpar o buffer de entrada
    }
    return numero;
}

// Função para exibir as opções de conversão
void exibirOpcoes() {
    printf("Escolha a base de conversão:\n");
    printf("1 - Decimal para Binário\n");
    printf("2 - Decimal para Octal\n");
    printf("3 - Decimal para Hexadecimal\n");
}

// Função principal do programa
int main() {
    int numero = obterEntradaUsuario();
    int opcao;

    exibirOpcoes();
    printf("Digite a opção: ");
    while (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 3) {
        printf("Opção inválida. Digite novamente (1-3): ");
        while(getchar() != '\n');  // Limpar o buffer de entrada
    }

    // Escolhe a base de conversão com base na opção fornecida
    if (opcao == 1) {
        conversaoDecimalParaBase(numero, BASE_BINARIO);
    } else if (opcao == 2) {
        conversaoDecimalParaBase(numero, BASE_OCTAL);
    } else if (opcao == 3) {
        conversaoDecimalParaBase(numero, BASE_HEXADECIMAL);
    }

    return 0;
}
