#include <stdlib.h>
#include <string.h>

typedef struct fila {
  int *dados;
  int N, p, u;
} fila;

int enfileira (fila *f, int x) {

    if (f->N == 0 || (f->u + 1) % f->N == f->p) { 
    int N_ant = f -> N;
    int tam_novo = (N_ant == 0) ? 16 : N_ant * 2;

    int *novos_dados = malloc(tam_novo * sizeof(int));
    if (novos_dados == NULL) return 0;

    int p_final = f->p;
    int u_final = f->u;

    if (N_ant == 0) { //se for primeira alocacao
        p_final = 0;
        u_final = 0;
    } else if (f->p > f->u) { 
        int size_p = N_ant - f->p;
        int size_u = f->u;

        if (size_p < size_u) { // se bloco 2 for menor q bloco 1
            // Copia o bloco 2 (de p a N-1) para o final do novo array
            memcpy(&novos_dados[tam_novo - size_p], &f->dados[f->p], size_p * sizeof(int));
            // Copia o bloco 1 (de 0 a u) para o inicio do novo array
            memcpy(&novos_dados[0], &f->dados[0], size_u * sizeof(int));
            p_final = tam_novo - size_p;
            
        } else { // contrario
            int i = 0;
            int j = f->p;
            while (j != f->u) {
                // Copia os dados do bloco 2 (de p a N-1) para o novo array
                novos_dados[f->p + i] = f->dados[j];
                i++;
                j = (j + 1) % N_ant;
            }
            // p_final
            u_final = f->p + i;
        }
        free(f->dados);
    } else { 
        // Copia os dados do bloco 1 (de p a u) para o novo array
        memcpy(&novos_dados[f->p], &f->dados[f->p], (f->u - f->p) * sizeof(int));
        free(f->dados);
    }

    f->dados = novos_dados;
    f->N = tam_novo;
    f->p = p_final;
    f->u = u_final;
    }
    // Insere o novo elemento na fila
    if (f->dados == NULL) return 0; // Verifica se a alocação foi bem-sucedida
    f->dados[f->u] = x;
    f->u = (f->u + 1) % f->N;
  
    return 1;
}