#include <stdlib.h>

typedef struct celula {
    int dado;
    struct celula *prox;
} celula;

celula *enfileira(celula *f, int x) {

    celula *nova = malloc(sizeof(celula)); // Aloca memória para a nova célula
    if (nova == NULL) return NULL; // Verifica alocação
    
    f->dado = x;
    nova->prox = f->prox;
    f->prox = nova;
    
    return nova;
}