#include "matching.h"

Matching *allocatesMatching(Graph *G) {
  Matching *M;
  M = malloc(sizeof(Matching));
  M->coveredVertices = malloc(G->n * sizeof(int));
  M->nVertices = G->n;
  M->maxEdges = G->maxEdges;
  M->size = 0;
  int i;
  for (i = 0; i < G->n; i++) {
    M->coveredVertices[i] = -1;
  }
  return M;
}

Matching *makeGreedyMatching(Graph *G) {
  Matching *M = allocatesMatching(G);

  int i;
  Vertex *neighbor;

  for (i = 0; i < G->n; i++) {
    if (G->exists[i]) {
      if (!isCovered(i, M)) {
        neighbor = G->vertices[i].next;
        while (neighbor != NULL) {
          if (!isCovered(neighbor->label, M)) {
            M->coveredVertices[i] = neighbor->label;
            M->coveredVertices[neighbor->label] = i;
            M->size++;
            neighbor = NULL; // essa linha serve para parar o while
          } else {
            neighbor = neighbor->next;
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
    if (M->coveredVertices[i] != -1) {
      if (i < M->coveredVertices[i]) {
        fprintf(foutptr, "|%d|---|%d|\n", i, M->coveredVertices[i]);
      }
    }
  }
}

bool isCovered(int vertex, Matching *M) {
  return (M->coveredVertices[vertex] != -1);
}
