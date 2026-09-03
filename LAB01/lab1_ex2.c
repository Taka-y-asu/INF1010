#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* top = NULL;

void exibe_pilha() {
    if (!top) { printf("[]\n"); return; }
    int arr[100], i = 0;
    Node* curr = top;
    while(curr) { arr[i++] = curr->data; curr = curr->next; }
    printf("[");
    for(int j = i - 1; j >= 0; j--) {
        printf("%d", arr[j]);
        if (j > 0) printf(", ");
    }
    printf("]\n");
}

void PUSH(int v) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->data = v; novo->next = top;
    top = novo;
    exibe_pilha();
}

int POP() {
    if (!top) return -1;
    Node* temp = top;
    int v = temp->data;
    top = top->next;
    free(temp);
    exibe_pilha();
    return v;
}

int main() {
    FILE *file = fopen("entrada_pilha.txt", "r");
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        char *token = strtok(linha, " \n\r");
        while (token) {
            if (token[0] == 'e') PUSH(atoi(token + 1));
            else if (token[0] == 'r') POP();
            token = strtok(NULL, " \n\r");
        }
    }
    fclose(file);
    return 0;
}