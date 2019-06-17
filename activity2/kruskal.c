/*
Author: Jonathan de Oliveira Cardoso (github.com/jonathancardoso)
References:
 - http://www.programasprontos.com/algoritmos-de-ordenacao/algortimo-quick-sort/
 - http://www.codcad.com/lesson/44
*/
#include <stdio.h>

#define MAXN 100
#define MAXM 200

struct aresta{
  int custo;
  int x,y;
} typedef tAresta;

// Protótipo da função de ordenação
// Ordination function prototype
void quick_sort(tAresta *a, int left, int right);

// para o union find
int pai[MAXN];
int peso[MAXN];

// a árvore
tAresta mst[MAXM];
//--------------------

// funções do union find
int find(int x){
    if(pai[x] == x) return x;
    return pai[x] = find(pai[x]);
}

void join(int a, int b){
    a = find(a);
    b = find(b);

    if(peso[a] < peso[b])
      pai[a] = b;
    else if(peso[b] < peso[a])
      pai[b] = a;
    else{
        pai[a] = b;
        peso[b]++;
    }
}

int main(){
    int n, m; // número de vértices e arestas
    int custo=0;
    tAresta aresta[MAXM];
    // ler a entrada
    printf("Digite a quantidade de vertices:\t");
    scanf("%i", &n);
    printf("Digite a quantidade de arestas:\t");
    scanf("%i", &m);
    int cities[n];

    printf("Preencha a entrada no formato: verticeA verticeB custo\n");
    for(int i = 1;i <= m;i++){
        scanf("%i %i %i",&aresta[i].x, &aresta[i].y, &aresta[i].custo);
    }
    // inicializar os pais para o union-find + zera cities
    for(int i = 1;i <= n;i++){
      pai[i] = i;
      cities[i] = 0;
    }
    // ordenar as arestas
    quick_sort(aresta, 0, aresta[MAXM-1].custo);

    int size = 0;
    for(int i = 1;i <= m;i++){
        if( find(aresta[i].x) != find(aresta[i].y) ){ // se estiverem em componentes distintas
            join(aresta[i].x, aresta[i].y);

            mst[++size] = aresta[i];
        }
    }

    // imprimir a MST + Calcular a Lista + Contar Adjacencias
    for(int i = 1;i < n;i++){
      //printf("%i %i %i\n", mst[i].x, mst[i].y, mst[i].custo);
      custo += mst[i].custo;
      cities[mst[i].x] +=1;
      cities[mst[i].y] +=1;
    }

    printf("Custo mínimo: %i\n", custo);
    printf("Cidades com mais de três linhas de transmissão:\n");
    for(int i = 1;i <= n;i++){
      if(cities[i]>3){
        printf("\tCitie [%i], conexions: %i\n",i, cities[i]);
      }
    }
    return 0;
}
