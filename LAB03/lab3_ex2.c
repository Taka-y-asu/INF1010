#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int chave;
    int altura; 
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

typedef struct avl {
    Nodo *raiz;
} AVL;

int altura(Nodo *n) {
    if (n == NULL) return -1;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fator_balanceamento(Nodo *n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

Nodo* criar_nodo_avl(int chave) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

Nodo* rotacao_direita(Nodo *y, const char* operacao) {
    printf("%s -> Rotação à direita (RD) no nó %d\n", operacao, y->chave);
    Nodo *x = y->esq;
    Nodo *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

Nodo* rotacao_esquerda(Nodo *x, const char* operacao) {
    printf("%s -> Rotação à esquerda (RE) no nó %d\n", operacao, x->chave);
    Nodo *y = x->dir;
    Nodo *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

Nodo* inserir_avl(Nodo *nodo, int chave, int *rotacao_feita) {
    if (nodo == NULL) return criar_nodo_avl(chave);

    if (chave < nodo->chave)
        nodo->esq = inserir_avl(nodo->esq, chave, rotacao_feita);
    else if (chave > nodo->chave)
        nodo->dir = inserir_avl(nodo->dir, chave, rotacao_feita);
    else
        return nodo;

    nodo->altura = 1 + max(altura(nodo->esq), altura(nodo->dir));
    int fb = fator_balanceamento(nodo);

    char op[50];
    sprintf(op, "Inserir %d", chave);

    if (fb > 1 && chave < nodo->esq->chave) {
        *rotacao_feita = 1;
        return rotacao_direita(nodo, op);
    }
    if (fb < -1 && chave > nodo->dir->chave) {
        *rotacao_feita = 1;
        return rotacao_esquerda(nodo, op);
    }
    if (fb > 1 && chave > nodo->esq->chave) {
        *rotacao_feita = 1;
        nodo->esq = rotacao_esquerda(nodo->esq, op);
        return rotacao_direita(nodo, op);
    }
    if (fb < -1 && chave < nodo->dir->chave) {
        *rotacao_feita = 1;
        nodo->dir = rotacao_direita(nodo->dir, op);
        return rotacao_esquerda(nodo, op);
    }

    return nodo;
}

void processar_insercao(AVL *arvore, int chave) {
    int rotacao_feita = 0;
    arvore->raiz = inserir_avl(arvore->raiz, chave, &rotacao_feita);
    if (!rotacao_feita) {
        printf("Inserir %d -> sem rotação.\n", chave);
    }
}

Nodo* nodo_minimo(Nodo *nodo) {
    Nodo *atual = nodo;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

Nodo* remover_avl(Nodo *raiz, int chave, int *rotacao_feita, int chave_removida) {
    if (raiz == NULL) return raiz;

    if (chave < raiz->chave)
        raiz->esq = remover_avl(raiz->esq, chave, rotacao_feita, chave_removida);
    else if (chave > raiz->chave)
        raiz->dir = remover_avl(raiz->dir, chave, rotacao_feita, chave_removida);
    else {
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            Nodo *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            free(temp);
        } else {
            Nodo *temp = nodo_minimo(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = remover_avl(raiz->dir, temp->chave, rotacao_feita, chave_removida);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    int fb = fator_balanceamento(raiz);

    char op[50];
    sprintf(op, "Remoção %d", chave_removida);

    if (fb > 1 && fator_balanceamento(raiz->esq) >= 0) {
        *rotacao_feita = 1;
        return rotacao_direita(raiz, op);
    }
    if (fb > 1 && fator_balanceamento(raiz->esq) < 0) {
        *rotacao_feita = 1;
        raiz->esq = rotacao_esquerda(raiz->esq, op);
        return rotacao_direita(raiz, op);
    }
    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0) {
        *rotacao_feita = 1;
        return rotacao_esquerda(raiz, op);
    }
    if (fb < -1 && fator_balanceamento(raiz->dir) > 0) {
        *rotacao_feita = 1;
        raiz->dir = rotacao_direita(raiz->dir, op);
        return rotacao_esquerda(raiz, op);
    }

    return raiz;
}

void processar_remocao(AVL *arvore, int chave) {
    int rotacao_feita = 0;
    arvore->raiz = remover_avl(arvore->raiz, chave, &rotacao_feita, chave);
    if (!rotacao_feita) {
        printf("Remoção %d -> sem rotação.\n", chave);
    }
}

void imprimir_arvore(Nodo *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        imprimir_arvore(raiz->esq);
        imprimir_arvore(raiz->dir);
    }
}

int main() {
    AVL arvore;
    arvore.raiz = criar_nodo_avl(50); 
    printf("Árvore iniciada com raiz 50.\n\n");

    int elementos_inserir[] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 43, 16, 67, 39};
    int n_inserir = sizeof(elementos_inserir) / sizeof(elementos_inserir[0]);

    printf("--- INSERÇÕES ---\n");
    for (int i = 0; i < n_inserir; i++) {
        processar_insercao(&arvore, elementos_inserir[i]);
    }

    printf("\nÁrvore completa após inserções (Pré-ordem): ");
    imprimir_arvore(arvore.raiz);
    printf("\n\n");

    int elementos_remover[] = {58, 59, 66, 18};
    int n_remover = sizeof(elementos_remover) / sizeof(elementos_remover[0]);

    printf("--- REMOÇÕES ---\n");
    for (int i = 0; i < n_remover; i++) {
        processar_remocao(&arvore, elementos_remover[i]);
    }

    printf("\nÁrvore final após remoções (Pré-ordem): ");
    imprimir_arvore(arvore.raiz);
    printf("\n");

    return 0;
}