#include "estruturas.h"
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

Emparelhamento* diferencaSimetrica(ArvoreAPS* T, Emparelhamento* M, int y) {
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
  return M;
}