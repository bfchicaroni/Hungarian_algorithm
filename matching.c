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
  M->maxEdges = G->maxEdges;
  M->size = 0;
  int i;
  for (i = 0; i < G->n; i++) {
    M->vEmparelhados[i] = -1;
  }
  return M;
}

Matching *makeGreedyMatching(Graph *G) {
  Matching *M = allocatesMatching(G);

  int i;
  Vertex *vizinho;

  for (i = 0; i < G->n; i++) {
    if (G->exists[i]) {
      if (!ehCoberto(i, M)) {
        vizinho = G->vertices[i].next;
        while (vizinho != NULL) {
          if (!ehCoberto(vizinho->label, M)) {
            M->vEmparelhados[i] = vizinho->label;
            M->vEmparelhados[vizinho->label] = i;
            M->size++;
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
  fprintf(foutptr, "%d\n", M->size);
  int i;
  for (i = 0; i < M->nVertices; i++) {
    if (M->vEmparelhados[i] != -1) {
      if (i < M->vEmparelhados[i]) {
        fprintf(foutptr, "|%d|---|%d|\n", i, M->vEmparelhados[i]);
      }
    }
  }
}

bool ehCoberto(int vertex, Matching *M) {
  return (M->vEmparelhados[vertex] != -1);
}
