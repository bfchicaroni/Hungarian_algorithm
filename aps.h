#include "matching.h"
#ifndef APS_H_
#define APS_H_

// Estrutura que representa a árvore APS
typedef struct APSTree {
  int *pai;
  bool *visitado;
  int nVertices;
} APSTree;

typedef struct TuplaAPS {
  bool foundMatching;
  APSTree *T;
  int u;
  bool *Rt;
  bool *Bt;
  int *Mt;
} TuplaAPS;

APSTree *allocatesTree(Graph *G);

void diferencaSimetrica(APSTree *T, Matching *M, int y);

TuplaAPS *APS(Graph *G, Matching *M, int u);
#endif