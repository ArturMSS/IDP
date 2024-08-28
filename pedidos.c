#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define NUM_PEDIDOS 10
#define MAX_ITENS 100

// Definição da estrutura para armazenar os dados dos pedidos dos clientes
typedef struct {
    int codigo;     // Código do item pedido
    int quantidade; // Quantidade do item pedido
} ItemPedido;

// Definição da estrutura para armazenar um pedido completo de um cliente
typedef struct {
    ItemPedido itens[MAX_ITENS]; // Lista de itens no pedido
    int num_itens;               // Número de itens no pedido
} Pedido;

// Função para exibir o cardápio para o cliente
void exibir_cardapio() {
    printf("Cardápio:\n");
    printf("1 - Cachorro-quente (Código 100) - R$ 5.20\n");
    printf("2 - Bauru simples (Código 101) - R$ 6.30\n");
    printf("3 - Bauru com ovo (Código 102) - R$ 6.50\n");
    printf("4 - Hambúrguer (Código 103) - R$ 7.20\n");
    printf("5 - Cheeseburguer (Código 104) - R$ 8.30\n");
    printf("6 - Refrigerante (Código 105) - R$ 5.00\n");
}

// Função para obter o preço do item com base no código
double obter_preco(int codigo) {
    switch (codigo) {
        case 100: return 5.20;  // Cachorro-quente
        case 101: return 6.30;  // Bauru simples
        case 102: return 6.50;  // Bauru com ovo
        case 103: return 7.20;  // Hambúrguer
        case 104: return 8.30;  // Cheeseburguer
        case 105: return 5.00;  // Refrigerante
        default: return 0.0;    // Código inválido
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Pedido pedidos[NUM_PEDIDOS]; // Array para armazenar os pedidos
    double faturamento_total = 0.0; // Inicialização do faturamento total

    // Loop para registrar 10 pedidos
    for (int i = 0; i < NUM_PEDIDOS; i++) {
        pedidos[i].num_itens = 0; // Inicializa o número de itens do pedido atual
        int continuar_pedido = 1; // Controle para continuar adicionando itens ao pedido

        printf("Pedido %d:\n", i + 1);

        // Loop para permitir que o cliente adicione vários itens em um pedido
        while (continuar_pedido) {
            exibir_cardapio(); // Exibe o cardápio para o cliente

            // Entrada do código do item
            printf("Digite o código do item: ");
            while (scanf("%d", &pedidos[i].itens[pedidos[i].num_itens].codigo) != 1 ||
                   (pedidos[i].itens[pedidos[i].num_itens].codigo < 100 || pedidos[i].itens[pedidos[i].num_itens].codigo > 105)) {
                printf("Código inválido. Insira um código entre 100 e 105: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }

            // Entrada da quantidade do item
            printf("Digite a quantidade: ");
            while (scanf("%d", &pedidos[i].itens[pedidos[i].num_itens].quantidade) != 1 ||
                   pedidos[i].itens[pedidos[i].num_itens].quantidade <= 0) {
                printf("Quantidade inválida. Insira um valor positivo: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }

            pedidos[i].num_itens++; // Incrementa o número de itens no pedido

            // Pergunta ao cliente se ele deseja adicionar mais itens ao pedido
            printf("Deseja adicionar mais um item? (1 - Sim, 0 - Não): ");
            scanf("%d", &continuar_pedido);
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        // Cálculo do valor total do pedido
        double valor_pedido = 0.0;
        for (int j = 0; j < pedidos[i].num_itens; j++) {
            double preco_unitario = obter_preco(pedidos[i].itens[j].codigo);
            valor_pedido += preco_unitario * pedidos[i].itens[j].quantidade;
        }
        faturamento_total += valor_pedido; // Acumula o valor no faturamento total

        printf("Valor do pedido: R$ %.2f\n\n", valor_pedido);
    }

    // Exibe o faturamento total do dia
    printf("Faturamento total do dia: R$ %.2f\n", faturamento_total);

    return 0;
}
