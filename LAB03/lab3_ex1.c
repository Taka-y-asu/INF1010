#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int chave;
    int altura;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

typedef struct abb {
    Nodo *raiz;
} ABB;

Nodo* criar_nodo(int chave) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->chave = chave;
    novo->altura = 0; 
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Nodo* inserir_abb(Nodo *raiz, int chave) {
    if (raiz == NULL) {
        return criar_nodo(chave);
    }
    if (chave < raiz->chave) {
        raiz->esq = inserir_abb(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = inserir_abb(raiz->dir, chave);
    }
    return raiz;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int atualizar_alturas(Nodo *raiz) {
    if (raiz == NULL) return -1;
    
    int alt_esq = atualizar_alturas(raiz->esq);
    int alt_dir = atualizar_alturas(raiz->dir);
    
    raiz->altura = max(alt_esq, alt_dir) + 1;
    return raiz->altura;
}

void pre_ordem(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d(%d) ", raiz->chave, raiz->altura);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

void ordem_simetrica(Nodo *raiz) {
    if (raiz != NULL) {
        ordem_simetrica(raiz->esq);
        printf("%d(%d) ", raiz->chave, raiz->altura);
        ordem_simetrica(raiz->dir);
    }
}

void por_nivel(Nodo *raiz) {
    if (raiz == NULL) return;
    
    Nodo* fila[100];
    int inicio = 0, fim = 0;
    
    fila[fim++] = raiz;
    
    while (inicio < fim) {
        Nodo *atual = fila[inicio++];
        printf("%d(%d) ", atual->chave, atual->altura);
        
        if (atual->esq != NULL) fila[fim++] = atual->esq;
        if (atual->dir != NULL) fila[fim++] = atual->dir;
    }
}

int main() {
    ABB arvore;
    arvore.raiz = NULL;
    
    FILE *ficheiro = fopen("entrada.txt", "r");
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro entrada.txt.\n");
        return 1;
    }
    
    int chave;
    while (fscanf(ficheiro, "%d", &chave) != EOF) {
        arvore.raiz = inserir_abb(arvore.raiz, chave);
    }
    fclose(ficheiro);
    
    atualizar_alturas(arvore.raiz);
    
    printf("Pré-ordem: ");
    pre_ordem(arvore.raiz);
    printf("\n");
    
    printf("Ordem Simétrica: ");
    ordem_simetrica(arvore.raiz);
    printf("\n");
    
    printf("Por nível: ");
    por_nivel(arvore.raiz);
    printf("\n");
    
    return 0;
}