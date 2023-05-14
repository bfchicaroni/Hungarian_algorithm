#include "matching.h"
#include "graph.h"
#include "structs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Matching *allocatesMatching(Graph *G) {
  Matching *M;
  M = malloc(sizeof(Matching));
  M->vEmparelhados = malloc(G->n * sizeof(int));
  M->nVertices = G->n;
  M->maxArestas = G->maxArestas;
  M->tamanho = 0;
  int i;
  for (i = 0; i < G->n; i++) {
    M->vEmparelhados[i] = -1;
  }
  return M;
}

Matching *makeGreedyMatching(Graph *G) {
  Matching *M = allocatesMatching(G);

  int i;
  Vertice *vizinho;

  for (i = 0; i < G->n; i++) {
    if (G->existe[i]) {
      if (!ehCoberto(i, M)) {
        vizinho = G->vertices[i].next;
        while (vizinho != NULL) {
          if (!ehCoberto(vizinho->rotulo, M)) {
            M->vEmparelhados[i] = vizinho->rotulo;
            M->vEmparelhados[vizinho->rotulo] = i;
            M->tamanho++;
            vizinho = NULL; // essa linha serve para parar o while
          } else {
            vizinho = vizinho->next;
          }
        }
      }
    }
  }
  return M;
}

void printMatching(Matching *M, FILE *foutptr) {
  fprintf(foutptr, "%d\n", M->tamanho);
  int i;
  for (i = 0; i < M->nVertices; i++) {
    if (M->vEmparelhados[i] != -1) {
      if (i < M->vEmparelhados[i]) {
        fprintf(foutptr, "|%d|---|%d|\n", i, M->vEmparelhados[i]);
      }
    }
  }
}

bool ehCoberto(int vertice, Matching *M) {
  return (M->vEmparelhados[vertice] != -1);
}