#include "estruturas.h"
#include "aps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ArvoreAPS* alocaArvore (Grafo* G) {
  ArvoreAPS *T;
  T = malloc(sizeof(ArvoreAPS));
  T->predecessor = malloc(G->n*sizeof(int));
  T->visitado = malloc(G->n*sizeof(bool));
  T->nVertices = G->n;
  int i;
  for (i = 0; i < T->nVertices; i++) {
    T->predecessor[i] = -1;
    T->visitado[i] = 0;
  }
  return T;
}

Emparelhamento* diferencaSimetrica(ArvoreAPS* T, Emparelhamento* M, int y) {
  int verticeAtual = y;
  while(T->predecessor[T->predecessor[verticeAtual]] != T->predecessor[verticeAtual]) {
    M->vEmparelhados[verticeAtual] = T->predecessor[verticeAtual];
    M->vEmparelhados[T->predecessor[verticeAtual]] = verticeAtual;
    verticeAtual = T->predecessor[verticeAtual];
    //M->vEmparelhados[T->predecessor[verticeAtual]] = -1;
    verticeAtual = T->predecessor[verticeAtual];
  }
  M->vEmparelhados[verticeAtual] = T->predecessor[verticeAtual];
  M->vEmparelhados[T->predecessor[verticeAtual]] = verticeAtual;
  M->tamanho++;
  return M;
}