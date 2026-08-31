#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int info;
    struct Node* prox;
} Node;

typedef struct Fila {
    Node* inicio;
    Node* fim;
} Fila;

void inicializaFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void ARMAZENA(int valor, Fila* f) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->info = valor;
    novo->prox = NULL;

    if (f->inicio == NULL) { 
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int RETIRA(Fila* f) {
    if (f->inicio == NULL) return -1; 

    Node* temp = f->inicio;
    int valor = temp->info;

    f->inicio = f->inicio->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return valor;
}

void limpaFila(Fila* f) {
    while (f->inicio != NULL) {
        RETIRA(f);
    }
}

void exibeFila(Fila* f) {
    printf("[");
    Node* atual = f->inicio;
    
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
        
        Fila f;
        inicializaFila(&f);


        char *token = strtok(linha, " \n\r");
        
        while (token != NULL) {
            if (token[0] == 'a') {
                int valor = atoi(&token[1]);
                ARMAZENA(valor, &f);
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