#include "prova2.h"

// Funções para manipulação de órgãos
Orgao* criarOrgao(int id, const char* tipo, const char* origem, const char* status) {
    Orgao* novo = (Orgao*)malloc(sizeof(Orgao));
    if (!novo) {
        printf("Erro ao alocar memória para o órgão.\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->tipo, tipo);
    strcpy(novo->origem, origem);
    strcpy(novo->status, status);
    return novo;
}

void liberarOrgao(Orgao** orgao) {
    if (!orgao || !*orgao) {
        fprintf(stderr, "Aviso: Tentativa de liberar ponteiro nulo ou já liberado.\n");
        return;
    }
    free(*orgao);
    *orgao = NULL; // Atualiza o ponteiro no escopo chamador
}

// Funções para manipulação de pilhas
void inicializarPilha(Pilha* pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha* pilha, Orgao* orgao) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if (!novo) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    novo->orgao = orgao;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

Orgao* desempilhar(Pilha* pilha) {
    if (!pilha->topo) return NULL;
    Nodo* topo = pilha->topo;
    Orgao* orgao = topo->orgao;
    pilha->topo = topo->prox;
    free(topo);
    return orgao;
}

// Funções para manipulação de filas
void inicializarFila(Fila* fila) {
    fila->inicio = fila->fim = NULL;
}

void enfileirar(Fila* fila, Orgao* orgao) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if (!novo) {
        printf("Erro ao alocar memória para a fila.\n");
        exit(1);
    }
    novo->orgao = orgao;
    novo->prox = NULL;
    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }
    fila->fim = novo;
}

Orgao* desenfileirar(Fila* fila) {
    if (!fila->inicio) return NULL;
    Nodo* inicio = fila->inicio;
    Orgao* orgao = inicio->orgao;
    fila->inicio = inicio->prox;
    if (!fila->inicio) fila->fim = NULL;
    free(inicio);
    return orgao;
}

// Funções para manipulação da lista global
void adicionarListaGlobal(Orgao* orgao) {
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if (!novo) {
        printf("Erro ao alocar memória para a lista global.\n");
        exit(1);
    }
    novo->orgao = orgao;
    novo->prox = listaGlobal.inicio;
    listaGlobal.inicio = novo;
}

void imprimirListaGlobal() {
    Nodo* atual = listaGlobal.inicio;
    while (atual) {
        printf("{id: %d, tipo: %s, origem: %s, status: %s} -> ",
               atual->orgao->id, atual->orgao->tipo, atual->orgao->origem, atual->orgao->status);
        atual = atual->prox;
    }
    printf("NULL\n");
}

void atualizarStatusListaGlobal(int id, const char* novoStatus) {
    Nodo* atual = listaGlobal.inicio;
    while (atual) {
        if (atual->orgao->id == id) {
            strcpy(atual->orgao->status, novoStatus);
            return;
        }
        atual = atual->prox;
    }
}

void adicionarDoacao(const char* capitalOrigem, const char* tipoOrgao, int algoritmoBusca) {
    int origem = obterIndiceCapital(capitalOrigem);
    if (origem == -1) {
        printf("Cidade de origem inválida.\n");
        return;
    }

    int cds[] = {6, 23, 5}; // Brasília, São Paulo, Fortaleza
    int cdMaisProximo = -1;
    int menorDistancia = INT_MAX;
    int caminhoFinal[MAX_CIDADES], tamanhoCaminho = 0;

    // Identificar o CD mais próximo
    for (int i = 0; i < 3; i++) {
        int caminhoAtual[MAX_CIDADES];
        int tamanhoAtual = 0;
        int distancia = calcularDistanciaComCaminho(origem, cds[i], algoritmoBusca, caminhoAtual, &tamanhoAtual);

        // Depuração: distâncias entre cidades
        printf("Cidade Origem: %s, CD: %s, Distância: %d\n", capitais[origem], capitais[cds[i]], distancia);

        if (distancia > 0 && distancia < menorDistancia) {
            menorDistancia = distancia;
            cdMaisProximo = cds[i];
            memcpy(caminhoFinal, caminhoAtual, sizeof(int) * tamanhoAtual);
            tamanhoCaminho = tamanhoAtual;
        }
    }

    if (cdMaisProximo == -1) {
        printf("Nenhum CD próximo encontrado. Verifique as conexões do grafo.\n");
        return;
    }

    // Imprimir os nós visitados e o caminho final
    imprime_nos_visitados(caminhoFinal);
    imprime_rota(caminhoFinal, tamanhoCaminho, menorDistancia);

    // Criar o órgão
    Orgao* novoOrgao = criarOrgao(idAtual++, tipoOrgao, capitalOrigem, "Em espera para transplante");
    adicionarListaGlobal(novoOrgao);

    // Adicionar o órgão ao CD correspondente
    if (strcmp(tipoOrgao, "CORAÇÃO") == 0) {
        if (cdMaisProximo == 6) {
            empilhar(&pilhaBrasilia, novoOrgao);
            printf("Órgão do tipo CORAÇÃO adicionado à pilha do CD Brasília.\n");
        } else if (cdMaisProximo == 23) {
            empilhar(&pilhaSaoPaulo, novoOrgao);
            printf("Órgão do tipo CORAÇÃO adicionado à pilha do CD São Paulo.\n");
        } else if (cdMaisProximo == 5) {
            empilhar(&pilhaFortaleza, novoOrgao);
            printf("Órgão do tipo CORAÇÃO adicionado à pilha do CD Fortaleza.\n");
        }
    } else if (strcmp(tipoOrgao, "MEDULA") == 0 || strcmp(tipoOrgao, "CÓRNEA") == 0) {
        if (cdMaisProximo == 6) {
            enfileirar(&filaBrasilia, novoOrgao);
            printf("Órgão do tipo %s adicionado à fila do CD Brasília.\n", tipoOrgao);
        } else if (cdMaisProximo == 23) {
            enfileirar(&filaSaoPaulo, novoOrgao);
            printf("Órgão do tipo %s adicionado à fila do CD São Paulo.\n", tipoOrgao);
        } else if (cdMaisProximo == 5) {
            enfileirar(&filaFortaleza, novoOrgao);
            printf("Órgão do tipo %s adicionado à fila do CD Fortaleza.\n", tipoOrgao);
        }
    } else {
        printf("Tipo de órgão desconhecido: %s. Nenhuma estrutura foi atualizada.\n", tipoOrgao);
        liberarOrgao(&novoOrgao);
    }

    // Depuração: estado das estruturas após adição
    printf("Estado após adição:\n");
    printf("Brasília: Pilha %s | Fila %s\n",
           pilhaBrasilia.topo ? "cheia" : "vazia",
           filaBrasilia.inicio ? "cheia" : "vazia");
    printf("São Paulo: Pilha %s | Fila %s\n",
           pilhaSaoPaulo.topo ? "cheia" : "vazia",
           filaSaoPaulo.inicio ? "cheia" : "vazia");
    printf("Fortaleza: Pilha %s | Fila %s\n",
           pilhaFortaleza.topo ? "cheia" : "vazia",
           filaFortaleza.inicio ? "cheia" : "vazia");
}

// Função para processar uma doação
void processarDoacao(const char* cidadePaciente, const char* tipoOrgao, int algoritmoBusca) {
    // Obter o índice da cidade do paciente
    int indiceCidadePaciente = obterIndiceCapital(cidadePaciente);
    if (indiceCidadePaciente == -1) {
        printf("Cidade inválida: %s. Por favor, tente novamente.\n", cidadePaciente);
        return;
    }

    // Definição dos CDs e inicialização de variáveis
    int cds[] = {6, 23, 5}; // Brasília, São Paulo, Fortaleza
    int cdMaisProximo = -1;
    int menorDistancia = INT_MAX;
    int caminhoFinal[MAX_CIDADES], tamanhoCaminho = 0;
    Orgao* orgaoProcessado = NULL;
    const char* cdOrigem = NULL;

    // Depuração: estado inicial das pilhas e filas
    printf("Estado inicial das estruturas:\n");

    const char* estadoPilhaBrasilia = pilhaBrasilia.topo ? "cheia" : "vazia";
    const char* estadoFilaBrasilia = filaBrasilia.inicio ? "cheia" : "vazia";
    printf("Brasília: Pilha %s | Fila %s\n", estadoPilhaBrasilia, estadoFilaBrasilia);

    const char* estadoPilhaSaoPaulo = pilhaSaoPaulo.topo ? "cheia" : "vazia";
    const char* estadoFilaSaoPaulo = filaSaoPaulo.inicio ? "cheia" : "vazia";
    printf("São Paulo: Pilha %s | Fila %s\n", estadoPilhaSaoPaulo, estadoFilaSaoPaulo);

    const char* estadoPilhaFortaleza = pilhaFortaleza.topo ? "cheia" : "vazia";
    const char* estadoFilaFortaleza = filaFortaleza.inicio ? "cheia" : "vazia";
    printf("Fortaleza: Pilha %s | Fila %s\n", estadoPilhaFortaleza, estadoFilaFortaleza);


    // Verificar se a cidade do paciente já é um CD
    for (int i = 0; i < 3; i++) {
        if (indiceCidadePaciente == cds[i]) {
            cdMaisProximo = cds[i];
            menorDistancia = 0;
            tamanhoCaminho = 1;
            caminhoFinal[0] = indiceCidadePaciente;
            break;
        }
    }

    // Caso a cidade não seja um CD, calcula o CD mais próximo
    if (cdMaisProximo == -1) {
        for (int i = 0; i < 3; i++) {
            int caminhoAtual[MAX_CIDADES];
            int tamanhoAtual = 0;
            int distancia = calcularDistanciaComCaminho(indiceCidadePaciente, cds[i], algoritmoBusca, caminhoAtual, &tamanhoAtual);

            // Verificar a disponibilidade do órgão no CD
            int disponivel = 0;
            if (strcmp(tipoOrgao, "CORAÇÃO") == 0) {
                disponivel = (cds[i] == 6 && pilhaBrasilia.topo) ||
                             (cds[i] == 23 && pilhaSaoPaulo.topo) ||
                             (cds[i] == 5 && pilhaFortaleza.topo);
            } else {
                disponivel = (cds[i] == 6 && filaBrasilia.inicio) ||
                             (cds[i] == 23 && filaSaoPaulo.inicio) ||
                             (cds[i] == 5 && filaFortaleza.inicio);
            }

            if (distancia > 0 && distancia < menorDistancia && disponivel) {
                menorDistancia = distancia;
                cdMaisProximo = cds[i];
                memcpy(caminhoFinal, caminhoAtual, sizeof(int) * tamanhoAtual);
                tamanhoCaminho = tamanhoAtual;
            }
        }
    }

    // Caso nenhum CD esteja disponível
    if (cdMaisProximo == -1) {
        printf("Nenhum órgão disponível do tipo %s próximo à cidade %s.\n", tipoOrgao, cidadePaciente);
        return;
    }

    // Imprimir os nós visitados e o caminho final usando as funções reutilizáveis
    imprime_nos_visitados(caminhoFinal);
    imprime_rota(caminhoFinal, tamanhoCaminho, menorDistancia);

    // Processar o órgão no CD mais próximo
    if (strcmp(tipoOrgao, "CORAÇÃO") == 0) {
        if (cdMaisProximo == 6) {
            orgaoProcessado = desempilhar(&pilhaBrasilia);
            cdOrigem = "Brasília";
        } else if (cdMaisProximo == 23) {
            orgaoProcessado = desempilhar(&pilhaSaoPaulo);
            cdOrigem = "São Paulo";
        } else if (cdMaisProximo == 5) {
            orgaoProcessado = desempilhar(&pilhaFortaleza);
            cdOrigem = "Fortaleza";
        }
    } else {
        if (cdMaisProximo == 6) {
            orgaoProcessado = desenfileirar(&filaBrasilia);
            cdOrigem = "Brasília";
        } else if (cdMaisProximo == 23) {
            orgaoProcessado = desenfileirar(&filaSaoPaulo);
            cdOrigem = "São Paulo";
        } else if (cdMaisProximo == 5) {
            orgaoProcessado = desenfileirar(&filaFortaleza);
            cdOrigem = "Fortaleza";
        }
    }

    // Atualizar e exibir resultados
    if (orgaoProcessado) {
        printf("Órgão processado do CD %s: {id: %d, tipo: %s, origem: %s}\n",
               cdOrigem, orgaoProcessado->id, orgaoProcessado->tipo, orgaoProcessado->origem);
        atualizarStatusListaGlobal(orgaoProcessado->id, "Órgão transplantado");
    } else {
        printf("Nenhum órgão disponível do tipo: %s no CD %s.\n", tipoOrgao, cdOrigem);
    }
}

// Função para exibir o estado das estruturas de dados
void exibirEstadoEstruturas() {

    // Variáveis auxiliares
    Nodo* atualPilha;
    Nodo* atualFila;
    Nodo* atualLista;

    // Exibir a pilha e fila de Brasília
    printf("\nPILHA BRASÍLIA:\n");
    atualPilha = pilhaBrasilia.topo;
    while (atualPilha) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualPilha->orgao->id, atualPilha->orgao->tipo, atualPilha->orgao->origem);
        atualPilha = atualPilha->prox;
    }

    printf("\nFILA BRASÍLIA:\n");
    atualFila = filaBrasilia.inicio;
    while (atualFila) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualFila->orgao->id, atualFila->orgao->tipo, atualFila->orgao->origem);
        atualFila = atualFila->prox;
    }

    // Exibir a pilha e fila de Fortaleza
    printf("\nPILHA FORTALEZA:\n");
    atualPilha = pilhaFortaleza.topo;
    while (atualPilha) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualPilha->orgao->id, atualPilha->orgao->tipo, atualPilha->orgao->origem);
        atualPilha = atualPilha->prox;
    }

    printf("\nFILA FORTALEZA:\n");
    atualFila = filaFortaleza.inicio;
    while (atualFila) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualFila->orgao->id, atualFila->orgao->tipo, atualFila->orgao->origem);
        atualFila = atualFila->prox;
    }

    // Exibir a pilha e fila de São Paulo
    printf("\nPILHA SÃO PAULO:\n");
    atualPilha = pilhaSaoPaulo.topo;
    while (atualPilha) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualPilha->orgao->id, atualPilha->orgao->tipo, atualPilha->orgao->origem);
        atualPilha = atualPilha->prox;
    }

    printf("\nFILA SÃO PAULO:\n");
    atualFila = filaSaoPaulo.inicio;
    while (atualFila) {
        printf("{id: %d; orgao: %s; origem: %s}\n",
               atualFila->orgao->id, atualFila->orgao->tipo, atualFila->orgao->origem);
        atualFila = atualFila->prox;
    }

    // Exibir a Lista Global
    printf("\nLISTA GLOBAL:\n");
    atualLista = listaGlobal.inicio;
    while (atualLista) {
        printf("{id: %d; orgao: %s; origem: %s; status: %s}\n",
               atualLista->orgao->id, atualLista->orgao->tipo, atualLista->orgao->origem, atualLista->orgao->status);
        atualLista = atualLista->prox;
    }
    printf("\n");
}

void inicializarListaGlobal() {
    listaGlobal.inicio = NULL;
}

void liberarEstruturas() {
    // Liberar as pilhas
    while (desempilhar(&pilhaBrasilia));
    while (desempilhar(&pilhaFortaleza));
    while (desempilhar(&pilhaSaoPaulo));

    // Liberar as filas
    while (desenfileirar(&filaBrasilia));
    while (desenfileirar(&filaFortaleza));
    while (desenfileirar(&filaSaoPaulo));

    // Liberar lista global
    Nodo* atual = listaGlobal.inicio;
    while (atual) {
        Nodo* prox = atual->prox;
        liberarOrgao(&(atual->orgao));
        free(atual);
        atual = prox;
    }
    listaGlobal.inicio = NULL;

    // Liberar grafo
    liberarGrafo();
}


void inicializarEstruturas() {
    inicializarPilha(&pilhaBrasilia);
    inicializarPilha(&pilhaFortaleza);
    inicializarPilha(&pilhaSaoPaulo);

    inicializarFila(&filaBrasilia);
    inicializarFila(&filaFortaleza);
    inicializarFila(&filaSaoPaulo);

    inicializarListaGlobal();

    inicializarGrafo();
    adicionarConexoes(); // Importante: chama a função para adicionar conexões
}


int validarCidade(const char* cidade) {
    if (!cidade) {
        printf("Erro: Cidade é NULL.\n");
        return 0;
    }

    for (int i = 0; i < MAX_CIDADES; i++) {
        if (capitais[i] && strncmp(capitais[i], cidade, 50) == 0) {
            return 1; // Cidade encontrada
        }
    }

    return 0; // Cidade não encontrada
}

int validarTipoOrgao(const char* tipo) {
    return (strcmp(tipo, "CORAÇÃO") == 0 || strcmp(tipo, "MEDULA") == 0 || strcmp(tipo, "CÓRNEA") == 0);
}

void listarCidades() {
    printf("Cidades disponíveis:\n");
    for (int i = 0; i < (MAX_CIDADES -1); i++) {
        printf("- %s - ", capitais[i]);
    }
    printf("Digite a capital desejada: \n");
}

void listarTiposOrgao() {
    printf("Tipos de órgãos disponíveis:\n");
    printf("- CORAÇÃO\n");
    printf("- MEDULA\n");
    printf("- CÓRNEA\n");
    printf("Digite o tipo de orgão escolhido: ");
}
