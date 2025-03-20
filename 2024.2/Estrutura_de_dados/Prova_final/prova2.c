#include <stdio.h>
#include "prova2.h"

// Inicialização das variáveis globais
Pilha pilhaBrasilia, pilhaFortaleza, pilhaSaoPaulo;
Fila filaBrasilia, filaFortaleza, filaSaoPaulo;
ListaGlobal listaGlobal = {NULL};
int idAtual = 1; // Inicialização do ID único
const char* capitais[MAX_CIDADES] = {
    "Rio Branco", "Maceió", "Macapá", "Manaus", "Salvador",
    "Fortaleza", "Brasília", "Vitória", "Goiânia", "São Luís",
    "Cuiabá", "Campo Grande", "Belo Horizonte", "Belém", "João Pessoa",
    "Curitiba", "Recife", "Teresina", "Rio de Janeiro", "Natal",
    "Porto Alegre", "Boa Vista", "Florianópolis", "São Paulo", "Aracaju",
    "Palmas", "Porto Velho"
};

// Função para inicializar as estruturas de dados
void inicializarEstruturas();
// Função para capturar e validar uma opção numérica
int escolherOpcao() {
    int opcao;
    printf("Escolha uma opção: ");
    while (scanf("%d", &opcao) != 1) {
        printf("Entrada inválida. Digite um número: ");
        // Limpa o buffer de entrada
        while (getchar() != '\n');
    }
    return opcao;
}

// Função para exibir o menu principal
void menuPrincipal() {
    printf("\n=== Sistema Nacional de Doações de Órgãos (SNDO) ===\n");
    printf("1. Adicionar doação\n");
    printf("2. Processar doação\n");
    printf("3. Exibir estado das estruturas de dados\n");
    printf("4. Configurar algoritmo de busca (1 = DFS, 2 = BFS)\n");
    printf("5. Sair\n");
}

int main() {
    int opcao = 0;
    int algoritmoBusca = 1;

    // Inicializar as estruturas de dados
    inicializarEstruturas();

    do {
        menuPrincipal();
        opcao = escolherOpcao();

        if (opcao == 1) {
            char capitalOrigem[50], tipoOrgao[10];

            listarCidades();
            scanf(" %[^\n]", capitalOrigem);

            if (!validarCidade(capitalOrigem)) {
                printf("Cidade inválida. Por favor, escolha uma das opções listadas.\n");
                continue;
            }

            listarTiposOrgao();
            scanf(" %[^\n]", tipoOrgao);

            if (!validarTipoOrgao(tipoOrgao)) {
                printf("Tipo de órgão inválido. Por favor, escolha uma das opções listadas.\n");
                continue;
            }

            adicionarDoacao(capitalOrigem, tipoOrgao, algoritmoBusca);

        } else if (opcao == 2) {
            char cidadePaciente[50], tipoOrgao[10];

            listarCidades();
            scanf(" %[^\n]", cidadePaciente);

            if (!validarCidade(cidadePaciente)) {
                printf("Cidade inválida. Por favor, escolha uma das opções listadas.\n");
                continue;
            }

            listarTiposOrgao();
            scanf(" %[^\n]", tipoOrgao);

            if (!validarTipoOrgao(tipoOrgao)) {
                printf("Tipo de órgão inválido. Por favor, escolha uma das opções listadas.\n");
                continue;
            }

            processarDoacao(cidadePaciente, tipoOrgao, algoritmoBusca);

        } else if (opcao == 3) {
            printf("Exibindo o estado atual das estruturas de dados...\n");
            exibirEstadoEstruturas();

        } else if (opcao == 4) {
            printf("\nEscolha o algoritmo de busca (1 = DFS, 2 = BFS): ");
            algoritmoBusca = escolherOpcao();

            if (algoritmoBusca == 1) {
                printf("Algoritmo configurado para DFS.\n");
            } else if (algoritmoBusca == 2) {
                printf("Algoritmo configurado para BFS.\n");
            } else {
                printf("Opção inválida. Mantendo o algoritmo atual.\n");
            }

        } else if (opcao == 5) {
            printf("\nEncerrando o programa...\n");
            liberarEstruturas();
            break;
        } else {
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 5);

    return 0;
}
