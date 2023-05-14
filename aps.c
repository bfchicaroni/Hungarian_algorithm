#include "aps.h"
#include "matching.h"
#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ArvoreAPS *alocaArvore(Graph *G) {
  ArvoreAPS *T;
  T = malloc(sizeof(ArvoreAPS));
  T->pai = malloc(G->n * sizeof(int));
  T->visitado = malloc(G->n * sizeof(bool));
  T->nVertices = G->n;
  int i;
  for (i = 0; i < T->nVertices; i++) {
    T->pai[i] = -1;
    T->visitado[i] = 0;
  }
  return T;
}

void diferencaSimetrica(ArvoreAPS *T, Matching *M, int y) {
  int verticeAtual = y;
  while (T->pai[T->pai[verticeAtual]] != T->pai[verticeAtual]) {
    M->vEmparelhados[verticeAtual] = T->pai[verticeAtual];
    M->vEmparelhados[T->pai[verticeAtual]] = verticeAtual;
    verticeAtual = T->pai[verticeAtual];
    // M->vEmparelhados[T->pai[verticeAtual]] = -1;
    verticeAtual = T->pai[verticeAtual];
  }
  M->vEmparelhados[verticeAtual] = T->pai[verticeAtual];
  M->vEmparelhados[T->pai[verticeAtual]] = verticeAtual;
  M->tamanho++;
}

TuplaAPS *alocaMemoriaAPS(Graph *G) {
  TuplaAPS *tupla;
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

TuplaAPS *APS(Graph *G, Matching *M, int u) {
  TuplaAPS *tupla = alocaMemoriaAPS(G);
  int *fila = malloc(G->n * sizeof(int));
  int ini = 0;
  int fim = 1;
  int x, y, z;

  fila[ini] = u;
  x = fila[ini];
  bool existeArestaXY = true;
  bool fimDosVizinhos = false;
  Vertice *vizX = G->vertices[x].next;
  tupla->foundMatching = false;
  tupla->T->visitado[x] = true;
  tupla->Rt[x] = true;
  tupla->T->pai[x] = x;

  do {
    do {
      if (vizX == NULL) {
        fimDosVizinhos = true;
        break;
      }
      y = vizX->rotulo;
      vizX = vizX->next;
    } while (tupla->T->visitado[y]);
    if (fimDosVizinhos) {
      if (ini != fim) {
        x = fila[ini];
        ini++;
        vizX = G->vertices[x].next;
        fimDosVizinhos = false;
      } else {
        existeArestaXY = false;
      }
    } else {
      tupla->T->visitado[y] = true;
      tupla->Bt[y] = true;
      tupla->T->pai[y] = x;
      z = M->vEmparelhados[y];
      if (z != -1) {
        fila[fim] = z;
        fim++;
        tupla->T->visitado[z] = true;
        tupla->Rt[z] = true;
        tupla->Mt[z] = y;
        tupla->Mt[y] = z;
        tupla->T->pai[z] = y;
      } else {
        tupla->foundMatching = true;
        diferencaSimetrica(tupla->T, M, y);
        // printf("[APS] Terminou com um novo emparelhamento\n");
        return tupla;
      }
    }
  } while (existeArestaXY);
  // printf("[APS] Nao achou novo emparelhamento\n");
  return tupla;
}