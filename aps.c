#include "estruturas.h"
#include "emparelhamento.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ArvoreAPS* alocaArvore (Grafo* G) {
  ArvoreAPS *T;
  T = malloc(sizeof(ArvoreAPS));
  T->pai = malloc(G->n*sizeof(int));
  T->visitado = malloc(G->n*sizeof(bool));
  T->nVertices = G->n;
  int i;
  for (i = 0; i < T->nVertices; i++) {
    T->pai[i] = -1;
    T->visitado[i] = 0;
  }
  return T;
}

void diferencaSimetrica(ArvoreAPS* T, Emparelhamento* M, int y) {
  int verticeAtual = y;
  while(T->pai[T->pai[verticeAtual]] != T->pai[verticeAtual]) {
    M->vEmparelhados[verticeAtual] = T->pai[verticeAtual];
    M->vEmparelhados[T->pai[verticeAtual]] = verticeAtual;
    verticeAtual = T->pai[verticeAtual];
    //M->vEmparelhados[T->pai[verticeAtual]] = -1;
    verticeAtual = T->pai[verticeAtual];
  }
  M->vEmparelhados[verticeAtual] = T->pai[verticeAtual];
  M->vEmparelhados[T->pai[verticeAtual]] = verticeAtual;
  M->tamanho++;
}

TuplaAPS* alocaMemoriaAPS (Grafo* G) {
  TuplaAPS* tupla;
  tupla = malloc(sizeof(TuplaAPS));
  tupla->T = alocaArvore(G);
  tupla->Rt = malloc(G->n * sizeof(bool));
  tupla->Bt = malloc(G->n * sizeof(bool));
  tupla->Mt = malloc(G->n * sizeof(int));

  int i;
  for (i = 0; i < G->n; i++) {
    tupla->Rt[i] = false;
    tupla->Bt[i] = false;
    tupla->Mt[i] = -1;
  }
  return tupla;
}

TuplaAPS* APS (Grafo* G, Emparelhamento* M, int u) {
  TuplaAPS* tupla = alocaMemoriaAPS(G);
  int* fila = malloc(G->n*sizeof(int));
  int ini = 0;
  int fim = 0;
  int x, y, z;
  printf("Memoria do APS alocada\n");
  
  fila[ini] = u;
  bool existeArestaXY = true;
  x = fila[ini];
  Vertice* vizX = G->vertices[x].next;
  y = vizX->rotulo;
  vizX = vizX->next;
  tupla->achouEmparelhamento = false;
  tupla->T->visitado[x] = true;
  tupla->Rt[x] = true;
  tupla->T->pai[x] = x;
  while(existeArestaXY) {
    printf("Entrou no laco com x = %d e y = %d\n", x, y);
    //y = vizX->rotulo;
    tupla->T->visitado[y] = true;
    tupla->Bt[y] = true;
    tupla->T->pai[y] = x;
    z = M->vEmparelhados[y];
    if(z == -1) {
      tupla->achouEmparelhamento = true;
      diferencaSimetrica(tupla->T, M, y);
      printf("Terminou com um novo emparelhamento\n");
      return tupla;
    }
    else { 
      printf("z = %d\n", z);
      tupla->T->visitado[z] = true;
      tupla->Rt[z] = true;
      tupla->Mt[z] = y;
      tupla->Mt[y] = z;
      tupla->T->pai[z] = y;
    }
    printf("Fim = %d", fim);
    fim++;
    fila[fim] = z;
    printf(" novo fim = %d\n", fim);
    while (tupla->T->visitado[y] && vizX != NULL) {
      printf("Entrou aqui\n");
      y = vizX->rotulo;
      printf("y = %d\n", y);
      vizX = vizX->next;
    }
    if (vizX == NULL) {
      ini++;
      printf("ini = %d ", ini);
      x = fila[ini];
      printf("x = %d\n", x);
      if (ini > fim) {
        existeArestaXY = false;
      } else {
        vizX = G->vertices[x].next;
        y = vizX->rotulo;
      }
    }
  }
  return tupla;
}