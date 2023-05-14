#include "aps.h"
#include "matching.h"
#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

APSTree *allocatesTree(Graph *G) {
  APSTree *T;
  T = malloc(sizeof(APSTree));
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

void diferencaSimetrica(APSTree *T, Matching *M, int y) {
  int currentVertex = y;
  while (T->pai[T->pai[currentVertex]] != T->pai[currentVertex]) {
    M->vEmparelhados[currentVertex] = T->pai[currentVertex];
    M->vEmparelhados[T->pai[currentVertex]] = currentVertex;
    currentVertex = T->pai[currentVertex];
    // M->vEmparelhados[T->pai[currentVertex]] = -1;
    currentVertex = T->pai[currentVertex];
  }
  M->vEmparelhados[currentVertex] = T->pai[currentVertex];
  M->vEmparelhados[T->pai[currentVertex]] = currentVertex;
  M->size++;
}

TuplaAPS *alocaMemoriaAPS(Graph *G) {
  TuplaAPS *tupla;
  tupla = malloc(sizeof(TuplaAPS));
  tupla->T = allocatesTree(G);
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
  bool edgeXYexists = true;
  bool fimDosVizinhos = false;
  Vertex *vizX = G->vertices[x].next;
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
      y = vizX->label;
      vizX = vizX->next;
    } while (tupla->T->visitado[y]);
    if (fimDosVizinhos) {
      if (ini != fim) {
        x = fila[ini];
        ini++;
        vizX = G->vertices[x].next;
        fimDosVizinhos = false;
      } else {
        edgeXYexists = false;
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
  } while (edgeXYexists);
  // printf("[APS] Nao achou novo emparelhamento\n");
  return tupla;
}