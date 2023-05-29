#include "aps.h"
#ifndef HUNGARO_H_
#define HUNGARO_H_

typedef struct HungarianTuple {
  APSTree **tau;
  bool *R;
  bool *B;
  Matching *Mstar;
  bool *U;
  Graph *F;
} HungarianTuple;

HungarianTuple *allocatesMemoryHungarian(Graph *G, Matching *M);

int searchUnmatched(Graph *G, Matching *M);

void unionOp(bool *A, bool *B, int size);

void matchingUnion(Matching *Mstar, Matching *M);

void matchingUnionArray(Matching *Mstar, int *M);

void removeMatching(Matching *M, APSTree *T);

void removeSubgraph(Graph *F, APSTree *T);

HungarianTuple *hungarian(Graph *G, Matching *M);

#endif