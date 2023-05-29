#include "matching.h"
#ifndef APS_H_
#define APS_H_

// Estrutura que representa a árvore APS
typedef struct APSTree {
  int *dad;
  bool *visited;
  int nVertices;
} APSTree;

typedef struct APSTuple {
  bool foundMatching;
  APSTree *T;
  int u;
  bool *Rt;
  bool *Bt;
  int *Mt;
} APSTuple;

APSTree *allocatesTree(Graph *G);

void diferencaSimetrica(APSTree *T, Matching *M, int y);

APSTuple *APS(Graph *G, Matching *M, int u);
#endif