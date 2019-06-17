//================================================================
// Nome Do Arquivo: quick.c
// File Name: quick.c
//
// Descrição: Implementação do algoritmo quicksort
// Description: Quick sort Algorithm
// Adaptado por Jonathan de Oliveira Cardoso (github.com/jonathancardoso)
//================================================================

// Libs
#include <stdio.h>
#include <stdlib.h>

struct aresta{
  int custo;
  int x,y;
} typedef tAresta;

// Protótipo da função de ordenação
// Ordination function prototype
void quick_sort(tAresta *a, int left, int right);

// Função de Ordenação por Seleção
// Quick sort function
void quick_sort(tAresta *a, int left, int right) {
    int i, j, x;
    tAresta y;

    i = left;
    j = right;
    x = a[(left + right) / 2].custo;

    while(i <= j) {
        while(a[i].custo < x && i < right) {
            i++;
        }
        while(a[j].custo > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, a[left].custo, a[j].custo);
    }
    if(i < right) {
        quick_sort(a, a[i].custo, a[right].custo);
    }
}
