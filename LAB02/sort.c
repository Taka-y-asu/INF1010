#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


void exibe_vetor(int *vet, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void preencheAleatorios(int *vet, int min, int max, int count) {
    unsigned int seed = time(0);
    for(int i = 0; i < count; i++) {
        vet[i] = rand_r(&seed) % (max - min + 1) + min;
    }
}

void bubble_sort(int *vet, int n) {
    printf("\n--- BubbleSort ---\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (vet[j] > vet[j+1]) {
                int temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
            }
        }
        printf("Iteracao %d: ", i + 1);
        exibe_vetor(vet, n);
    }
}

void selection_sort(int *vet, int n) {
    printf("\n--- SelectionSort ---\n");
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (vet[j] < vet[min_idx]) {
                min_idx = j;
            }
        }
        int temp = vet[i];
        vet[i] = vet[min_idx];
        vet[min_idx] = temp;
        
        printf("Iteracao %d: ", i + 1);
        exibe_vetor(vet, n);
    }
}

int main(void) {
    int min = 0, max = 100, count = 10;
    int vet_bubble[10];
    int vet_selection[10];
    
    preencheAleatorios(vet_bubble, min, max, count);
    
    for (int i = 0; i < count; i++) {
        vet_selection[i] = vet_bubble[i];
    }
    
    printf("Vetor original gerado: ");
    exibe_vetor(vet_bubble, count);
    
    bubble_sort(vet_bubble, count);
    
    selection_sort(vet_selection, count);
    
    return 0;
}