#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int info;
    struct Node * prox;
} node;

typedef struct Fila {
    node * inicio;
    node * fim;
} fila;

void inicializaFila(fila * f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void ARMAZENA(fila * f, int v) {
    node * novo = (node*) malloc(sizeof(node));
    novo->info = v;
    novo->prox = NULL;
    
    if (f->inicio == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int RETIRA(fila * f) {
    if (f->inicio == NULL) return -1; 

    node* temp = f->inicio;
    int valor = temp->info;

    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return valor;
}

void limpaFila(fila* f) {
    while (f->inicio != NULL) {
        RETIRA(f);
    }
}

void exibeFila(fila* f) {
    printf("[");
    node* atual = f->inicio;
    
    while (atual != NULL) {
        printf("%d", atual->info); 
        if (atual->prox != NULL) {
            printf(", ");
        }
        atual = atual->prox;
    }
    printf("]\n");
}

int main() {
    FILE *arquivo = fopen("entrada_fila.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo entrada_fila.txt\n");
        return 1;
    }

    char linha[256];
    int num_linha = 1;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("--- Processando Linha %d ---\n", num_linha++);
        
        fila f; 
        inicializaFila(&f);

        char *token = strtok(linha, " \n\r");
        
        while (token != NULL) {
            if (token[0] == 'a') {
                int valor = atoi(&token[1]);
                ARMAZENA(&f, valor); 
                exibeFila(&f);
            } 
            else if (token[0] == 'r') {
                RETIRA(&f);
                exibeFila(&f);
            }

            token = strtok(NULL, " \n\r");
        }
        
        limpaFila(&f);
        printf("\n");
    }

    fclose(arquivo);
    return 0;
}