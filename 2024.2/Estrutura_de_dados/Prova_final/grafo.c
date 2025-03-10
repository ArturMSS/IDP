#include "prova2.h"

GrafoAdj grafo[MAX_CIDADES];

// Inicializa o grafo com base nas conexões diretas fornecidas
void inicializarGrafo() {
    for (int i = 0; i < MAX_CIDADES; i++) {
        grafo[i].listaAdj = NULL;
    }
}

void adicionarAresta(int origem, int destino) {
    NodoAdjacente* novo = (NodoAdjacente*)malloc(sizeof(NodoAdjacente));
    if (!novo) {
        printf("Erro ao alocar memória para a aresta.\n");
        exit(1);
    }
    novo->destino = destino;
    novo->prox = grafo[origem].listaAdj;
    grafo[origem].listaAdj = novo;
}


void adicionarConexoes() {
    adicionarAresta(0, 3); adicionarAresta(3, 0); // Rio Branco <-> Manaus
    adicionarAresta(3, 21); adicionarAresta(21, 3); // Manaus <-> Boa Vista
    adicionarAresta(3, 13); adicionarAresta(13, 3); // Manaus <-> Belém
    adicionarAresta(21, 13); adicionarAresta(13, 21); // Boa Vista <-> Belém
    adicionarAresta(2, 13); adicionarAresta(13, 2); // Macapá <-> Belém
    adicionarAresta(13, 6); adicionarAresta(6, 13); // Belém <-> Brasília
    adicionarAresta(13, 9); adicionarAresta(9, 13); // Belém <-> São Luís
    adicionarAresta(9, 17); adicionarAresta(17, 9); // São Luís <-> Teresina
    adicionarAresta(9, 25); adicionarAresta(25, 9); // São Luís <-> Palmas
    adicionarAresta(9, 5); adicionarAresta(5, 9); // São Luís <-> Fortaleza
    adicionarAresta(17, 25); adicionarAresta(25, 17); // Teresina <-> Palmas
    adicionarAresta(5, 6); adicionarAresta(6, 5); // Fortaleza <-> Brasília
    adicionarAresta(5, 19); adicionarAresta(19, 5); // Fortaleza <-> Natal
    adicionarAresta(25, 6); adicionarAresta(6, 25);; // Palmas <-> Brasília
    adicionarAresta(19, 14); adicionarAresta(14, 19); // Natal <-> João Pessoa
    adicionarAresta(14, 16); adicionarAresta(16, 14); // João Pessoa <-> Recife
    adicionarAresta(16, 1); adicionarAresta(1, 16); // Recife <-> Maceió
    adicionarAresta(1, 24); adicionarAresta(24, 1); // Maceió <-> Aracaju
    adicionarAresta(24, 4); adicionarAresta(4, 24); // Aracaju <-> Salvador
    adicionarAresta(4, 6); adicionarAresta(6, 4); // Salvador <-> Brasília
    adicionarAresta(6, 12); adicionarAresta(12, 6); // Brasília <-> Belo Horizonte
    adicionarAresta(12, 18); adicionarAresta(18, 12); // Belo Horizonte <-> Rio de Janeiro
    adicionarAresta(12, 23); adicionarAresta(23, 12); // Belo Horizonte <-> São Paulo
    adicionarAresta(18, 7); adicionarAresta(7, 18); // Rio de Janeiro <-> Vitória
    adicionarAresta(18, 23); adicionarAresta(23, 18); // Rio de Janeiro <-> São Paulo
    adicionarAresta(23, 15); adicionarAresta(15, 23); // São Paulo <-> Curitiba
    adicionarAresta(15, 22); adicionarAresta(22, 15); // Curitiba <-> Florianópolis
    adicionarAresta(22, 20); adicionarAresta(20, 22); // Florianópolis <-> Porto Alegre
    adicionarAresta(23, 11); adicionarAresta(11, 23); // São Paulo <-> Campo Grande
    adicionarAresta(23, 6); adicionarAresta(6, 23); // São Paulo <-> Brasília
    adicionarAresta(11, 8); adicionarAresta(8, 11); // Campo Grande <-> Goiânia
    adicionarAresta(8, 6); adicionarAresta(6, 8); // Goiânia <-> Brasília
    adicionarAresta(10, 11); adicionarAresta(11, 10); // Cuiabá <-> Campo Grande
    adicionarAresta(10, 6); adicionarAresta(6, 10); // Cuiabá <-> Brasília
    adicionarAresta(26, 3); adicionarAresta(3, 26); // Porto Velho <-> Manaus
}

int obterIndiceCapital(const char* capital) {
    // Validação de entrada nula ou vazia
    if (capital == NULL || capital[0] == '\0') {
        fprintf(stderr, "Erro: Nenhuma capital foi fornecida.\n");
        return -1;
    }

    // Comparação para encontrar o índice da capital
    for (int i = 0; i < MAX_CIDADES; i++) {
        if (strcasecmp(capitais[i], capital) == 0) { // Ignora diferenças de maiúsculas/minúsculas
            return i;
        }
    }

    // Mensagem de erro se a capital não for encontrada
    fprintf(stderr, "Erro: A capital '%s' não é válida. Verifique a lista de capitais disponíveis.\n", capital);
    return -1;
}
void imprime_rota(int caminhoFinal[MAX_CIDADES], int tamanhoCaminho, int distanciaTotal) {
    printf("Caminho encontrado: ");
    for (int i = 0; i < tamanhoCaminho; i++) {
        printf("%s%s", capitais[caminhoFinal[i]], (i == tamanhoCaminho - 1) ? "\n" : " -> ");
    }
    printf("Distância total: %d\n", distanciaTotal);
}

void imprime_nos_visitados(int visitados[MAX_CIDADES]) {
    printf("Nós visitados durante a busca: ");
    for (int i = 0; i < MAX_CIDADES; i++) {
        if (visitados[i]) {
            printf("%s ", capitais[i]);
        }
    }
    printf("\n");
}

// Algoritmo de busca em largura (BFS) para verificar conectividade
int bfsComCaminho(int origem, int destino, int* distanciaTotal, int* caminhoFinal, int* tamanhoCaminho) {
    if (origem == destino) {
        *distanciaTotal = 0;
        *tamanhoCaminho = 1;
        caminhoFinal[0] = origem;
        return 1; // Caminho encontrado
    }

    int visitados[MAX_CIDADES] = {0};
    int fila[MAX_CIDADES], inicio = 0, fim = 0;
    int pai[MAX_CIDADES];

    for (int i = 0; i < MAX_CIDADES; i++) {
        pai[i] = -1;
    }

    fila[fim++] = origem;
    visitados[origem] = 1;

    while (inicio < fim) {
        int atual = fila[inicio++];
        NodoAdjacente* adj = grafo[atual].listaAdj;

        while (adj) {
            if (!visitados[adj->destino]) {
                visitados[adj->destino] = 1;
                pai[adj->destino] = atual;
                fila[fim++] = adj->destino;

                if (adj->destino == destino) {
                    // Reconstrói o caminho final
                    int indice = destino;
                    *tamanhoCaminho = 0;
                    *distanciaTotal = 0;

                    while (indice != -1) {
                        caminhoFinal[(*tamanhoCaminho)++] = indice;
                        if (pai[indice] != -1) {
                            (*distanciaTotal)++;
                        }
                        indice = pai[indice];
                    }

                    // Inverte o caminho para exibição correta
                    for (int i = 0; i < *tamanhoCaminho / 2; i++) {
                        int temp = caminhoFinal[i];
                        caminhoFinal[i] = caminhoFinal[*tamanhoCaminho - i - 1];
                        caminhoFinal[*tamanhoCaminho - i - 1] = temp;
                    }

                    return 1; // Caminho encontrado
                }
            }
            adj = adj->prox;
        }
    }

    *distanciaTotal = -1; // Caminho não encontrado
    return 0;
}
int dfsComCaminhoAux(int origem, int destino, int visitados[MAX_CIDADES], int* caminhoTemporario, int tamanhoTemporario, 
                     int* caminhoFinal, int* tamanhoCaminho, int* distanciaTotal, int pai[MAX_CIDADES], int* menorDistancia) {
    // Marca o nó como visitado
    visitados[origem] = 1;
    caminhoTemporario[tamanhoTemporario++] = origem;

    if (origem == destino) {
        if (tamanhoTemporario - 1 < *menorDistancia) {
            *menorDistancia = tamanhoTemporario - 1;
            *tamanhoCaminho = tamanhoTemporario;
            *distanciaTotal = *menorDistancia;

            // Atualiza o caminho final
            for (int i = 0; i < tamanhoTemporario; i++) {
                caminhoFinal[i] = caminhoTemporario[i];
            }
        }

        // Desmarca o nó antes de retornar
        visitados[origem] = 0;
        return 1; // Caminho encontrado
    }

    NodoAdjacente* adj = grafo[origem].listaAdj;
    while (adj) {
        if (!visitados[adj->destino]) {
            pai[adj->destino] = origem;

            dfsComCaminhoAux(adj->destino, destino, visitados, caminhoTemporario, tamanhoTemporario, 
                             caminhoFinal, tamanhoCaminho, distanciaTotal, pai, menorDistancia);
        }
        adj = adj->prox;
    }

    // Backtracking
    visitados[origem] = 0;
    return *menorDistancia != INT_MAX ? 1 : 0; // Retorna 1 se encontrou caminho
}

int dfsComCaminho(int origem, int destino, int visitados[MAX_CIDADES], int* caminhoFinal, int* tamanhoCaminho, 
                  int* distanciaTotal, int pai[MAX_CIDADES]) {
    int menorDistancia = INT_MAX;
    int caminhoTemporario[MAX_CIDADES];
    int tamanhoTemporario = 0;

    return dfsComCaminhoAux(origem, destino, visitados, caminhoTemporario, tamanhoTemporario, 
                            caminhoFinal, tamanhoCaminho, distanciaTotal, pai, &menorDistancia);
}

int calcularDistanciaComCaminho(int origem, int destino, int algoritmoBusca, int* caminhoFinal, int* tamanhoCaminho) {
    int distanciaTotal = 0;

    if (algoritmoBusca == 1) { // DFS
        int visitados[MAX_CIDADES] = {0}, pai[MAX_CIDADES];
        for (int i = 0; i < MAX_CIDADES; i++) {
            pai[i] = -1;
        }

        if (dfsComCaminho(origem, destino, visitados, caminhoFinal, tamanhoCaminho, &distanciaTotal, pai)) {
            return distanciaTotal;
        }
    } else if (algoritmoBusca == 2) { // BFS
        if (bfsComCaminho(origem, destino, &distanciaTotal, caminhoFinal, tamanhoCaminho)) {
            return distanciaTotal;
        }
    }

    return -1; // Caminho não encontrado
}

void imprimirGrafo() {
    for (int i = 0; i < MAX_CIDADES; i++) {
        printf("%s: ", capitais[i]);
        NodoAdjacente* adj = grafo[i].listaAdj;
        while (adj) {
            printf("-> %s ", capitais[adj->destino]);
            adj = adj->prox;
        }
        printf("\n");
    }
}

void liberarGrafo() {
    for (int i = 0; i < MAX_CIDADES; i++) {
        NodoAdjacente* atual = grafo[i].listaAdj;
        while (atual) {
            NodoAdjacente* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        grafo[i].listaAdj = NULL; // Garante que o grafo não aponte para memória inválida
    }
}