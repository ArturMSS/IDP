#ifndef PROVA2_H
#define PROVA2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#define MAX_CIDADES 27

// Estruturas de Dados
typedef struct Orgao {
    int id;                 // Identificador único
    char tipo[10];          // Tipo do órgão: CORAÇÃO, MEDULA, CÓRNEA
    char origem[50];        // Capital de origem
    char status[30];        // Status: "Em espera para transplante" ou "Órgão transplantado"
} Orgao;

typedef struct Nodo {
    Orgao* orgao;
    struct Nodo* prox;
} Nodo;

typedef struct Pilha {
    Nodo* topo;
} Pilha;

typedef struct Fila {
    Nodo* inicio;
    Nodo* fim;
} Fila;

typedef struct ListaGlobal {
    Nodo* inicio;
} ListaGlobal;

typedef struct NodoAdjacente {
    int destino;
    struct NodoAdjacente* prox;
} NodoAdjacente;

typedef struct {
    NodoAdjacente* listaAdj; // Lista ligada para armazenar os vizinhos
} GrafoAdj;

// Grafo representado como lista de adjacência
extern GrafoAdj grafo[MAX_CIDADES];

// Variáveis globais
extern Pilha pilhaBrasilia, pilhaFortaleza, pilhaSaoPaulo;
extern Fila filaBrasilia, filaFortaleza, filaSaoPaulo;
extern ListaGlobal listaGlobal;
extern int idAtual;
extern const char* capitais[MAX_CIDADES];

// Funções para manipulação de órgãos
Orgao* criarOrgao(int id, const char* tipo, const char* origem, const char* status);
void liberarOrgao(Orgao** orgao);

// Funções para manipulação de pilhas
void inicializarPilha(Pilha* pilha);
void empilhar(Pilha* pilha, Orgao* orgao);
Orgao* desempilhar(Pilha* pilha);

// Funções para manipulação de filas
void inicializarFila(Fila* fila);
void enfileirar(Fila* fila, Orgao* orgao);
Orgao* desenfileirar(Fila* fila);

// Funções para manipulação da lista global
void inicializarListaGlobal();
void adicionarListaGlobal(Orgao* orgao);
void imprimirListaGlobal();
void atualizarStatusListaGlobal(int id, const char* novoStatus);

// Funções de manipulação do grafo
void inicializarGrafo();
void adicionarAresta(int origem, int destino);
void adicionarConexoes();
void imprimirGrafo();
void liberarGrafo();
int obterIndiceCapital(const char* capital);
// Funções de busca no grafo
int bfsComCaminho(int origem, int destino, int* distanciaTotal, int* caminhoFinal, int* tamanhoCaminho);
int dfsComCaminho(int origem, int destino, int visitados[MAX_CIDADES], int* caminhoFinal, int* tamanhoCaminho, int* distanciaTotal, int pai[MAX_CIDADES]);
int dfsComCaminhoAux(int origem, int destino, int visitados[MAX_CIDADES], int* caminhoTemporario, int tamanhoTemporario, 
                     int* caminhoFinal, int* tamanhoCaminho, int* distanciaTotal, int pai[MAX_CIDADES], int* menorDistancia);
int calcularDistanciaComCaminho(int origem, int destino, int algoritmoBusca, int* caminhoFinal, int* tamanhoCaminho);
void imprime_nos_visitados(int visitados[MAX_CIDADES]);
void imprime_rota(int caminhoFinal[MAX_CIDADES], int tamanhoCaminho, int distanciaTotal);
// Funções principais do programa
void adicionarDoacao(const char* capitalOrigem, const char* tipoOrgao, int algoritmoBusca);
void processarDoacao(const char* cidadePaciente, const char* tipoOrgao, int algoritmoBusca);
void exibirEstadoEstruturas();
void liberarEstruturas();

// Validação de entradas
int validarCidade(const char* cidade);
int validarTipoOrgao(const char* tipo);
// extra n sei do q chamar
void listarTiposOrgao();
void listarCidades();
#endif // PROVA2_H
