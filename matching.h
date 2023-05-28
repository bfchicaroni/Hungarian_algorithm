#include "graph.h"
#ifndef MATCHING_H_
#define MATCHING_H_

// Estrutura que representa um emparelhamento.
typedef struct Matching {
  int *vEmparelhados;
  int nVertices;
  int size;
  int maxEdges;
} Matching;

bool isMatching(Graph *G, Matching *M);

Matching *allocatesMatching(Graph *G);

Matching *makeGreedyMatching(Graph *G);

void printMatching(Matching *M, FILE *foutptr);

bool ehCoberto(int vertex, Matching *M);

#endif